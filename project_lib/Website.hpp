#ifndef CONTACTS_EXPLORER_WEBSITE_HPP
#define CONTACTS_EXPLORER_WEBSITE_HPP

#include <vector>

#include "ContactRecord.hpp"
#include "Page/DetailsPage.hpp"
#include "Page/IndexPage.hpp"
#include "WebsiteSettings.hpp"

/** A website that has one index page and multiple details pages. */
class Website {

public:

    /** Website constructor. Requires settings so in/out directories are known.
     * @param settings The settings.
     */
    explicit Website(WebsiteSettings settings);

    /** Adds contact records to the website, creating new details pages and
     * updating the index page accordingly.
     * @param records Vector of `ContactRecord`s.
     */
    void addContactRecords(std::vector<ContactRecord> records);

    /** Writes the website to disk.
     * @param inDir The input directory for data. Requires trailing slash.
     * @param outDir The output directory.
     *               **WARNING:** Contents will be overwritten!
     */
    void writeToDisk();

    /** @return The index page. */
    IndexPage getIndexPage();

    /** @return The details pages. */
    std::vector<DetailsPage> getDetailsPages();

private:
    IndexPage indexPage_;
    std::vector<DetailsPage> detailsPages_;
    WebsiteSettings settings_;
    void writeIndexPage(std::string outDir);
    void writeDetailsPages();
    void writeCSS(std::string inDir, std::string outDir);

    template <typename T> // Must be passed by reference to compile!
    std::string replaceTemplates(const std::string& inDir, T& page);

};

#endif //CONTACTS_EXPLORER_WEBSITE_HPP
