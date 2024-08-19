#include <algorithm>
#include "IndexPage.hpp"
#include "Element/Heading.hpp"
#include "Element/List.hpp"
#include "Element/Hyperlink.hpp"
#include "Element/Container.hpp"

IndexPage::IndexPage(const WebsiteSettings::IndexSettings& settings)
: settings_{settings}, alphaStart_{settings.capitalInitials ? 'A' : 'a'} {

}

void IndexPage::generateAnchors() {
    for (const DetailsPage& page : detailsPages_) {
        addPageToAnchor(page);
    }
}

void IndexPage::addText(const std::string& text) {
    userText_.append(text);
}

std::string IndexPage::toString() {
    std::string html;
    if (settings_.enableAnchors) {
        html.append(createAnchorsContainer().toString());
    }
    html.append(userText_);
    html.append(createNamesContainer().toString());
    return html;
}

Container IndexPage::createAnchorsContainer() {

    Container container(std::string("anchors"));

    // Anchor links. Letters without any names are present but not linked.
    for (unsigned i = 0; i < 27; i++) {
        if (i == 26) {
            if (anchors_[i].empty()) container.add(settings_.omega).add("\n");
            else container.add(Hyperlink(settings_.omega).toString());
        } else {
            if (anchors_[i].empty()) {
                container.add(std::string(1, alphaStart_ + i)).add("\n");
            } else {
                container.add(Hyperlink("#" + std::string(1, alphaStart_ + i)).toString());
            }
        }
    }

    container.add(Hyperlink("#", "Top").toString())
             .add(Hyperlink("#footer", "Bottom").toString());

    return container;
}

Container IndexPage::createNamesContainer() {
    Container container(std::string("names"));

    // Headings and contents
    for (unsigned i = 0; i < 27; i++) {
        if (!anchors_[i].empty()) {
            container.add(headingToString(i))
                     .add(linksToString(i));
        }
    }
    return container;
}

std::string IndexPage::headingToString(unsigned letterIndex) {
    std::sort(anchors_[letterIndex].begin(), anchors_[letterIndex].end());
    std::string str;
    if (letterIndex == 26) {
        str.append(Heading(2, settings_.omega).toString());
    } else {
        str.append(Heading(2, std::string(1, alphaStart_ + letterIndex)).toString());
    }
    return str;
}

std::string IndexPage::linksToString(unsigned letterIndex) {
    List list;
    for (DetailsPage page : anchors_[letterIndex]) {
        std::unique_ptr<Page> pagePointer {new DetailsPage(page)};
        Hyperlink link{pagePointer, page.getTitle()};
        list.addItem(link.toString());
    }
    return list.toString();
}

std::string IndexPage::getTitle() {
    return settings_.title;
}

std::string IndexPage::getUrl() {
    return "index.html";
}

void IndexPage::addPageToAnchor(DetailsPage page) {
    // Iterate through alphabet
    for (char initial = alphaStart_; initial <= 'Z'; initial++) {
        if (toupper(page.getContact().getLastName()[0]) == initial) {
            anchors_[initial - alphaStart_].emplace_back(page);
            return;
        }
    }
    // If not in alphabet, add to miscellaneous character
    anchors_[26].emplace_back(page);
}

void IndexPage::generateLinks(std::vector<DetailsPage> detailsPages) {
    detailsPages_.swap(detailsPages);
    generateAnchors();
}
