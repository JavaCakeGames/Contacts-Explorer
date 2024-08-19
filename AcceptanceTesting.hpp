#ifndef CONTACTS_EXPLORER_ACCEPTANCETESTING_HPP
#define CONTACTS_EXPLORER_ACCEPTANCETESTING_HPP

#include "Website.hpp"

class AcceptanceTesting {

public:

    explicit AcceptanceTesting(const WebsiteSettings& settings);

    /** **Use case 1:** Read a text file from the local file system. */
    void readTextFile();

    /** **Use case 2:**
     * Display all contacts (contact details) in a console window, in raw format ie
     * without HTML tagging.
     */
    void displayAllContacts();

    /** **Use case 3:**
     * Retrieve and display a single contact record (ie all contact details) in a
     * console window.
     */
    void displaySingleRecord();

    /** **Use case 4:**
     * Generate and display the HTML source code of the index page in a console
     * window. The HTML must be well-formed; only the doc type HTML 5 is acceptable.
     * The index page must contain hyperlinks for EACH of the contact records.
     */
    void displayIndexSource();

    /** **Use case 5:**
     * Add HTML elements to the index page (in particular: paragraphs and
     * hyperlinks).
     */
    void addElementsToIndex();

    /** **Use case 6:**
     * Generate and display the HTML source code of a details page in a console
     * window. The HTML must be well-formed; only the doc type HTML 5 is acceptable.
     * Each details page must contain a hyperlink to the index page.
     */
    void displayDetailsSource();

    /** **Use case 7:**
     * Add HTML elements to any of the linked pages (in particular: paragraphs).
     * Optional: add CSS code.
     */
    void addElementsToDetails();

    /** **Use case 8:**
     * Generate HTML source code for an index page and all details pages. Write a
     * file for EACH of the generated pages to disk.
     */
    void generateAndSaveWebsite();

private:
    Website website_;
    std::string csvPath_;

};

#endif //CONTACTS_EXPLORER_ACCEPTANCETESTING_HPP
