#include "Container.hpp"

#include <utility>

Container::Container() {

}

Container::Container(Types type)
: type_{type} {

}

Container::Container(Types type, std::string contents)
: type_{type}, contents_{std::move(contents)} {

}

Container::Container(std::string className)
: className_{std::move(className)} {

}

Container::Container(std::string className, Types type)
: className_{std::move(className)}, type_{type} {

}

Container::Container(std::string className, Types type, std::string contents)
: className_{std::move(className)}, type_{type},
  contents_{std::move(contents)} {

}

std::string Container::toString() {
    std::string container;

    switch(type_) {
        case Types::DIV: container.append("<div"); break;
        case Types::SPAN: container.append("<span"); break;
        case Types::P: container.append("<p"); break;
        case Types::CODE: container.append("<code"); break;
    }

    if (!className_.empty())
        container.append(" class='").append(className_).append("'");

    container.append(">\n") // Close the tag
             .append(contents_);

    switch(type_) {
        case Types::DIV: container.append("\n</div>\n"); break;
        case Types::SPAN: container.append("\n</span>\n"); break;
        case Types::P: container.append("\n</p>\n"); break;
        case Types::CODE: container.append("\n</code>\n"); break;
    }

    return container;
}

Container& Container::add(const std::string& text) {
    contents_.append(text);
    return *this;
}
