#ifndef CONTACTS_EXPLORER_INDEXPAGE_HPP
#define CONTACTS_EXPLORER_INDEXPAGE_HPP

#include <vector>

#include "Page.hpp"
#include "DetailsPage.hpp"
#include "Element/Element.hpp"
#include "Element/Container.hpp"
#include "WebsiteSettings.hpp"

/**
 * The index page holds links to each contact record.
 *
 * To make these easier to navigate, they are sorted alphabetically in ascending
 * order by surname then forename. Anchor links are provided for each letter to
 * aid with navigation.
 *
 * **Limitation:**
 * Anchors are generated for A-Z only and do not account for accents.
 * E.g. "Álvarez" would be grouped at the end under "Ω".
 */
class IndexPage : public Page {

public:

    /**
     * Create an index page / homepage.
     * @param settings Index page settings.
     */
    explicit IndexPage(const WebsiteSettings::IndexSettings& settings);

    /** Add text to the index page, including HTML. */
    void addText(const std::string& text) override;

    /** @return The entire index page as a string. */
    std::string toString() override;

    /** @return The index page's title, e.g. "Index Page". */
    std::string getTitle() override;

    /** @return The index page's address, e.g. "index.html". */
    std::string getUrl() override;

    /** Generates links to detail pages.
     * @param detailsPage A vector of `DetailsPage`s.
     */
    void generateLinks(std::vector<DetailsPage> detailsPage);

private:
    void generateAnchors();
    std::vector<DetailsPage> detailsPages_;
    std::vector<DetailsPage> anchors_[27];
    void addPageToAnchor(DetailsPage page);
    Container createAnchorsContainer();
    Container createNamesContainer();
    std::string headingToString(unsigned letterIndex);
    std::string linksToString(unsigned letterIndex);
    WebsiteSettings::IndexSettings settings_;
    char alphaStart_;
    std::string userText_;

};

#endif //CONTACTS_EXPLORER_INDEXPAGE_HPP
