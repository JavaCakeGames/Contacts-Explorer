#ifndef CONTACTS_EXPLORER_PAGE_HPP
#define CONTACTS_EXPLORER_PAGE_HPP

#include <string>

/** A page. This class is to be derived. */
class Page {

public:

    /** Adds text to the page, including HTML. */
    virtual void addText(const std::string& text);

    /** @return The entire page as a string. */
    virtual std::string toString();

    /** @return The title displayed in the browser's title bar */
    virtual std::string getTitle();

    /** @return The page address/filename, typically ending in `.html`. */
    virtual std::string getUrl();


};

#endif //CONTACTS_EXPLORER_PAGE_HPP
