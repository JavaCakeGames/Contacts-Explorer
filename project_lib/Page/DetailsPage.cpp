#include "DetailsPage.hpp"
#include "IndexPage.hpp"
#include "Element/Hyperlink.hpp"
#include "Element/Table.hpp"
#include "WebsiteSettings.hpp"

#include <utility>
#include <algorithm>

DetailsPage::DetailsPage(ContactRecord record, unsigned total,
                         const WebsiteSettings::DetailsSettings& settings
) : contact_{std::move(record)}, totalRecords_{total}, settings_{settings},
    digits_(std::to_string(totalRecords_).length()) {

}

DetailsPage::DetailsPage(
    ContactRecord record, ContactRecord prevRecord, ContactRecord nextRecord,
    unsigned total, const WebsiteSettings::DetailsSettings& settings
) : contact_{std::move(record)}, prevRecord_{std::move(prevRecord)},
    nextRecord_{std::move(nextRecord)}, totalRecords_{total},
    settings_{settings}, digits_(std::to_string(totalRecords_).length()) {

}

void DetailsPage::addText(const std::string& text) {
    userText_.append(text);
}

std::string DetailsPage::toString() {
    std::string html;

    std::unique_ptr<Page> pagePointer {
        new IndexPage(WebsiteSettings::IndexSettings())
    };

    html.append(userText_);

    html.append(createDetailsTable());
    if (settings_.enablePrevNextName) html.append(createNameLinks());
    if (settings_.enablePrevNextId) html.append(createIdLinks());
    if (settings_.enableRandom) html.append(createRandLink());

    return html;

}

std::string DetailsPage::getTitle() {
    std::string name;
    name.append(contact_.getLastName()).append(", ")
        .append(contact_.getFirstName());
    return name;
}

std::string DetailsPage::getUrl() {
    std::string url;
    auto digits = std::to_string(totalRecords_).length();
    url.append(settings_.prefix)
       .append(contact_.getPaddedId(digits))
       .append(settings_.suffix);
    return url;
}

ContactRecord DetailsPage::getContact() {
    return contact_;
}

std::string DetailsPage::createDetailsTable() {
    Table table(true);
    table.addRow(std::vector<std::string> {
        "ID", std::to_string(contact_.getId())
    });
    table.addRow(std::vector<std::string> {
        "First name", contact_.getFirstName()
    });
    table.addRow(std::vector<std::string> {
        "Last name", contact_.getLastName()
    });
    table.addRow(std::vector<std::string> {
        "Email address", contact_.getEmail()
    });
    table.addRow(std::vector<std::string> {
        "Country", contact_.getCountry()
    });
    return table.toString();
}

std::string DetailsPage::createNameLinks() {
    Container container;
    if (prevRecord_.getId() >= 0) {
        std::unique_ptr<Page> prevPointer{
            new DetailsPage(prevRecord_, totalRecords_, settings_)
        };
        Hyperlink prevLink = Hyperlink(prevPointer, "Previous Name");
        container.add(prevLink.toString());
    }
    if (nextRecord_.getId() >= 0) {
        std::unique_ptr<Page> nextPointer{
            new DetailsPage(nextRecord_, totalRecords_, settings_)
        };
        Hyperlink nextLink = Hyperlink(nextPointer, "Next Name");
        container.add(nextLink.toString());
    }
    return container.toString();
}

std::string DetailsPage::createIdLinks() {
    Container container;
    if (contact_.getId() > 1) {
        std::string url;
        url.append(settings_.prefix)
           .append(contact_.getPaddedId(digits_, contact_.getId() - 1))
           .append(settings_.suffix);
        Hyperlink prevIdLink = Hyperlink(url, "Previous ID");
        container.add(prevIdLink.toString());
    }
    if (contact_.getId() < totalRecords_) {
        std::string url;
        url.append(settings_.prefix)
                .append(contact_.getPaddedId(digits_, contact_.getId() + 1))
                .append(settings_.suffix);
        Hyperlink nextIdLink = Hyperlink(url, "Next ID");
        container.add(nextIdLink.toString());
    }
    return container.toString();
}

std::string DetailsPage::createRandLink() const {
    std::string js = {"javascript:"};
    // For details on this nightmare, see header file
    js.append("window.location = \"").append(settings_.prefix).append("\" + ")
      .append("Math.floor(1 + Math.random() * ") // One-indexing
      .append(std::to_string(totalRecords_))
      .append(").toString().padStart(").append(std::to_string(digits_))
      .append(", \"0\")").append(" + \"").append(settings_.suffix).append("\"");
    return Hyperlink(js, "Random").toString();
}

bool DetailsPage::operator < (DetailsPage& detailsPage) const {
    // Convert to lowercase for case-insensitive comparison
    std::string page1 =
            contact_.getLastName().append(contact_.getFirstName());
    std::transform(page1.begin(), page1.end(), page1.begin(), ::tolower);
    std::string page2 =
            detailsPage.getContact().getLastName()
                       .append(detailsPage.getContact().getFirstName());
    std::transform(page2.begin(), page2.end(), page2.begin(), ::tolower);
    return page1 < page2;
}
