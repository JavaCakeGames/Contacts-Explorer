#ifndef CONTACTS_EXPLORER_LIST_HPP
#define CONTACTS_EXPLORER_LIST_HPP

#include <vector>
#include "Element.hpp"

/**
 * A list element - `<ol>` or `<ul>` depending on if it's ordered or unordered.
 * The individual list items are also handled by this class.
 */
class List : public Element {

public:

    /** Create an unordered list (bullet points). */
    List();

    /** Create a list.
     * @param ordered True if it should be ordered (1, 2, 3...)
     *                or false for unordered (bullet points).
     */
    explicit List(bool ordered);

    /** Adds a single item to the list.
     * @param item Item contents as a string. Can contain HTML.
     * @return Self as a pointer for chaining.
     */
    List& addItem(const std::string& item);

    /** @return The list as a string. */
    std::string toString() override;

private:
    bool ordered_ = false;
    std::vector<std::string> items_;

};

#endif //CONTACTS_EXPLORER_LIST_HPP
