#include <iostream>
#include "AcceptanceTesting.hpp"
#include "TextFileLoader.hpp"
#include "WebsiteSettings.hpp"
#include "Website.hpp"
#include "Element/Hyperlink.hpp"

AcceptanceTesting::AcceptanceTesting(const WebsiteSettings& settings)
: website_{Website(settings)} {

    csvPath_.append(settings.inPath).append("contacts.csv");
    TextFileLoader textFileLoader{csvPath_};
    auto records = textFileLoader.getContactRecords();

    website_.addContactRecords(records);
}

void AcceptanceTesting::readTextFile() {
    TextFileLoader loader(csvPath_);
    loader.process(); // Read the file but do nothing with it.
}

void AcceptanceTesting::displayAllContacts() {
    TextFileLoader loader(csvPath_);
    std::vector<ContactRecord> records = loader.getContactRecords();
    for (auto record : records) {
        std::cout << record.getAsCsv();
    }
}

void AcceptanceTesting::displaySingleRecord() {
    TextFileLoader loader(csvPath_);
    std::vector<ContactRecord> records = loader.getContactRecords();
    std::cout << records[0].getAsPlainText();
}

void AcceptanceTesting::displayIndexSource() {
    std::cout << website_.getIndexPage().toString();
}

void AcceptanceTesting::addElementsToIndex() {
    Container paragraph(Container::Types::P, "Check out my cool website:");
    website_.getIndexPage().addText(paragraph.toString());
    Hyperlink link("https://example.org/", "Example Domain", true);
    website_.getIndexPage().addText(link.toString());
}

void AcceptanceTesting::displayDetailsSource() {
    // Output the source of the first details page.
    std::cout << website_.getDetailsPages()[0].toString();
}

void AcceptanceTesting::addElementsToDetails() {
    Container paragraph1(Container::Types::P, "Attention! Attention!");
    Container paragraph2(Container::Types::P,
                         "This employee no longer works here.");
    Container paragraph3(Container::Types::P, "They will not be replaced.");

    // Add paragraphs to first details page.
    website_.getDetailsPages()[0].addText(paragraph1.toString());
    website_.getDetailsPages()[0].addText(paragraph2.toString());
    website_.getDetailsPages()[0].addText(paragraph3.toString());
}

void AcceptanceTesting::generateAndSaveWebsite() {
    // The website is already generated, so it just needs saving.
    website_.writeToDisk();
}
