#ifndef CONTACTS_EXPLORER_DETAILSPAGE_HPP
#define CONTACTS_EXPLORER_DETAILSPAGE_HPP

#include "ContactRecord.hpp"
#include "Page.hpp"
#include "WebsiteSettings.hpp"

/**
 * The details page for a single contact record.
 * This page displays the record's ID, full name, email and country.
 * There are also links provided to return to the homepage, proceed to the next
 * or previous contact record alphabetically or by ID, and to navigate to a
 * random contact record.
 */
class DetailsPage : public Page {

public:

    /** Create a details page without Previous/Next Name navigation links.
     * @param record Contact record.
     * @param total The total number of records (for zero-padding).
     * @param settings Details page settings.
     */
    DetailsPage(ContactRecord record, unsigned total,
                const WebsiteSettings::DetailsSettings& settings);

    /** Create a details page with Previous/Next Name navigation links.
     * @param record The contact record to display the details of.
     * @param prevRecord The previous contact record alphabetically. If its ID
     *                   is negative, a "Previous Name" link is not displayed.
     * @param nextRecord The next contact record alphabetically. If its ID is
     *                   negative, a "Next Name" link is not displayed.
     * @param total The total number of records (for zero-padding).
     * @param settings Details page settings.
     */
    DetailsPage(
        ContactRecord record, ContactRecord prevRecord,
        ContactRecord nextRecord, unsigned total,
        const WebsiteSettings::DetailsSettings& settings
    );

    /** Add text to this page, including HTML. */
    void addText(const std::string& text) override;

    /** @return The entire page as a string. */
    std::string toString() override;

    /** @return The title for this page. Surname, comma, forename. */
    std::string getTitle() override;

    /** The URL for this page, e.g. `details-0123.html`. */
    std::string getUrl() override;

    /** @return This page's contact record. */
    ContactRecord getContact();

    /** Less-than operator used for case-insensitive sorting by last name then
     * first name. */
    bool operator < (DetailsPage& detailsPage) const;

private:
    std::string createDetailsTable();
    std::string createNameLinks();
    std::string createIdLinks();

    /** Creates a "Random" link which takes the user to a random contact record.
     * It passes JavaScript into the link's href to jump to a random contact
     * record without requiring server hosting.
     * If the user has JavaScript disabled, it will not work.
     * @return "Random" link as string
     */
    [[nodiscard]] std::string createRandLink() const;

    ContactRecord contact_;
    ContactRecord prevRecord_;
    ContactRecord nextRecord_;
    unsigned totalRecords_;
    unsigned digits_;
    WebsiteSettings::DetailsSettings settings_;
    std::string userText_;

};

#endif //CONTACTS_EXPLORER_DETAILSPAGE_HPP
