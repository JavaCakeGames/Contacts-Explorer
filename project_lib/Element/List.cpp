#include "List.hpp"

List::List() {
}

List::List(bool ordered) : ordered_{ordered} {
}

List& List::addItem(const std::string& item) {
    items_.emplace_back(item);
    return *this;
}

std::string List::toString() {
    std::string xl;
    xl.append(ordered_ ? "<ol>" : "<ul>").append("\n");
    for (const auto& item : items_) {
        xl.append("<li>\n\t").append(item).append("</li>\n");
    }
    xl.append(ordered_ ? "</ol>" : "</ul>").append("\n");
    return xl;
}
