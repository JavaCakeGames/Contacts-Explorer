#ifndef CONTACTS_EXPLORER_CONTAINER_HPP
#define CONTACTS_EXPLORER_CONTAINER_HPP

#include "Element.hpp"

/** An HTML block-level or inline container. */
class Container : public Element {

public:

    /** The type of element the container is.
     * A container can be one of several elements.
     * For more complex elements such as lists, see the other Element classes.
     */
    enum class Types {
        DIV, SPAN, P, CODE
    };

    /** Creates a block-level container (div). */
    Container();

    /**
     * Creates a container of the given type.
     * @param type The type of element.
     */
    explicit Container(Types type);

    /** Creates a container of the given type and contents.
     * @param type The type of the element.
     * @param contents The contents within the element.
     */
    Container(Types type, std::string contents);

    /** Creates a div container.
     * @param className The name of the class, e.g. to style with CSS.
     */
    explicit Container(std::string className);

    /** Creates a container with the given class name and type.
     * @param className The name of the class, e.g. to style with CSS.
     * @param inlined The type of element.
     */
    Container(std::string className, Types type);

    /** Creates a container with the given class name, type, and contents.
     * @param className The name of the class, e.g. to style with CSS.
     * @param type The type of the element.
     * @param contents The contents within the element.
     */
    Container(std::string className, Types type, std::string contents);

    /** @return The container as a string */
    std::string toString() override;

    /** Adds text, like `append()` in std library.
     * @param text The text to add.
     * @return Self as a pointer for chaining.
     */
    Container& add(const std::string& text);

private:
    std::string className_;
    bool inlined_ {false};
    Types type_ {Types::DIV};
    std::string contents_;

};

#endif //CONTACTS_EXPLORER_CONTAINER_HPP
