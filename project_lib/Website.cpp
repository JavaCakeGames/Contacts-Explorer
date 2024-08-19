#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <utility>
#include "Website.hpp"
#include "WebsiteSettings.hpp"

Website::Website(WebsiteSettings settings)
: settings_{std::move(settings)}, indexPage_(settings.index) {
}

void Website::addContactRecords(std::vector<ContactRecord> records) {

    // Must be sorted for previous/next links to function correctly
    std::sort(records.begin(), records.end());

    for (unsigned i = 0; i < records.size(); i++) {

        ContactRecord nullRecord = ContactRecord();

        // Pass previous and next pages only if they exist.
        // Otherwise, pass a "null"/dummy record.
        bool hasPrev = i > 0;
        bool hasNext = i < records.size() - 1;
        if (hasPrev && hasNext) {
            detailsPages_.emplace_back(
                records[i], records[i - 1], records[i + 1], records.size(),
                settings_.details);
        } else if (hasPrev) {
            detailsPages_.emplace_back(
                records[i], records[i - 1], nullRecord, records.size(),
                settings_.details);
        } else if (hasNext) {
            detailsPages_.emplace_back(
                    records[i], nullRecord,
                    records[i + 1], records.size(), settings_.details);
        } else { // Neither
            detailsPages_.emplace_back(records[i], records.size(),
                                       settings_.details);
        }
    }
    indexPage_.generateLinks(detailsPages_);
}

void Website::writeToDisk() {
    writeIndexPage(settings_.outPath);
    writeDetailsPages();
    writeCSS(settings_.inPath, settings_.outPath);
}

void Website::writeIndexPage(std::string outDir) {
    std::ofstream out(outDir.append("index.html"));
    out << replaceTemplates(settings_.inPath, indexPage_);
    out.close();
}

void Website::writeDetailsPages() {
    for (auto page : detailsPages_) {
        std::ofstream out(settings_.outPath + page.getUrl());
        out << replaceTemplates(settings_.inPath, page);
        out.close();
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"
void Website::writeCSS(std::string inDir, std::string outDir) {
    inDir.append("stylesheet.css");
    outDir.append("stylesheet.css");
    std::filesystem::copy_file(
            inDir, outDir,
            std::filesystem::copy_options::overwrite_existing
    );
}
#pragma clang diagnostic pop

template <typename T>
std::string Website::replaceTemplates(const std::string& inDir, T& page) {
    std::ifstream htmlTemplate(inDir + "template.html");
    const std::string htmlTemplateStr { (std::istreambuf_iterator<char>(htmlTemplate) ),
                                        (std::istreambuf_iterator<char>()) };

    const std::string mainSearch {settings_.templateSettings.main};
    const std::string titleSearch {settings_.templateSettings.title};

    std::string str = std::string(htmlTemplateStr);

    // https://stackoverflow.com/a/3418260
    str.replace(str.find(mainSearch), size(mainSearch), page.toString());
    str.replace(str.find(titleSearch), size(titleSearch), page.getTitle());

    return str;
}

IndexPage Website::getIndexPage() {
    return indexPage_;
}

std::vector<DetailsPage> Website::getDetailsPages() {
    return detailsPages_;
}


