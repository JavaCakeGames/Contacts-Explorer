#ifndef CONTACTS_EXPLORER_ELEMENT_HPP
#define CONTACTS_EXPLORER_ELEMENT_HPP

#include <string>

/** An HTML element. This class is to be derived from. */
class Element {

public:
    /**
     * Virtual function for serialising the element as a string
     * @return Element as string, typically expected but not guaranteed to end in a newline
     */
    virtual std::string toString() = 0;

};


#endif //CONTACTS_EXPLORER_ELEMENT_HPP
