#ifndef CONTACTS_EXPLORER_HEADING_HPP
#define CONTACTS_EXPLORER_HEADING_HPP

#include "Element.hpp"

/** A heading element - h1, h2, h3, h4, h5, h6 */
class Heading : public Element {

public:
    /**
     * @param level Heading level. Must be 1 through 6 as per HTML spec
     * @param contents The text displayed by the heading
     */
    Heading(const int& level, const std::string& contents);

    /** Return heading as string. */
    std::string toString() override;

private:
    int level_; // h1 through h6
    std::string contents_;
    std::string idAttribute_;

};

#endif //CONTACTS_EXPLORER_HEADING_HPP
