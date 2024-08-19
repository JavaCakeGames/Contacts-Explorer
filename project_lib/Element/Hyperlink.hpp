#ifndef CONTACTS_EXPLORER_HYPERLINK_HPP
#define CONTACTS_EXPLORER_HYPERLINK_HPP

#include <string>
#include <memory>
#include "Page/Page.hpp"
#include "Element.hpp"

/** A hyperlink element - `<a>`. */
class Hyperlink : public Element {

public:

    // Constructors with pointers are in header file to avoid linker error

    /** Create a hyperlink that uses a given page's address and title.
     * @tparam T `DetailsPage` or `IndexPage`.
     * @param linkedPage The page to be linked to.
     */
    template<typename T>
    explicit Hyperlink(std::unique_ptr<T> &linkedPage)
    : url_{linkedPage -> getUrl()}, contents_{linkedPage->getTitle()} {
    }

    /** Create a hyperlink from the given page's address and custom text.
     * @tparam T `DetailsPage` or `IndexPage`.
     * @param linkedPage The page to be linked to.
     * @param contents The text associated with the link (e.g. "click here").
     */
    template<typename T>
    Hyperlink(std::unique_ptr<T> &linkedPage, std::string contents)
    : url_{linkedPage -> getUrl()}, contents_{std::move(contents)} {

    }

    /**
     * Create a hyperlink from the given page's address and custom text.
     * @tparam T `DetailsPage` or `IndexPage`.
     * @param linkedPage The page to be linked to.
     * @param contents The text associated with the link (e.g. "click here").
     * @param newTab Whether the link should be opened in a new tab.
     */
    template<typename T>
    Hyperlink(std::unique_ptr<T> &linkedPage, std::string contents, bool newTab)
    : url_(linkedPage -> getUrl()), contents_{std::move(contents)},
      newTab_{newTab} {
    }

    /** Create a hyperlink to an address.
     * @param url Relative or absolute address to link to. May include protocol.
     */
    explicit Hyperlink(std::string url);

    /**
     * Create a hyperlink to an address with custom text.
     * @param url Relative or absolute address to link to. May include protocol.
     * @param contents The text associated with the link (e.g. "click here").
     */
    Hyperlink(std::string url, std::string contents);

    /**
     * Create a hyperlink to an address with custom text.
     * @param url Relative or absolute address to link to. May include protocol.
     * @param contents The text associated with the link (e.g. "click here").
     * @param newTab Whether the link should be opened in a new tab.
     */
    Hyperlink(std::string url, std::string contents, bool newTab);

    /** @return The hyperlink as a string. */
    std::string toString() override;

private:
    std::string contents_;
    std::string url_;
    bool newTab_ = false;

};

#endif //CONTACTS_EXPLORER_HYPERLINK_HPP
