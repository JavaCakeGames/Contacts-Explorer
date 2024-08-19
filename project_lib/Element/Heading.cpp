#include <stdexcept>
#include <algorithm>
#include <regex>
#include "Heading.hpp"

Heading::Heading(const int& level, const std::string& contents)
: level_{level}, contents_{contents}, idAttribute_{contents} {

    if (!(level >= 1 && level <= 6)) {
        throw std::invalid_argument{"Headings must be level 1 to 6"};
    }

    // Replace "ASCII whitespace" with underscores
    // https://html.spec.whatwg.org/multipage/dom.html#the-id-attribute
    std::regex_replace(idAttribute_, std::regex("\t\n\f\r "), "_");
    // Escape apostrophes as these are used in toString()
    std::regex_replace(idAttribute_, std::regex("'"), "\\'");

}

std::string Heading::toString() {
    std::string lvlStr = std::to_string(level_);
    std::string hx;                                      // Example:
    hx.append("\n<h").append(lvlStr)                     // \n<h2
      .append(" id='").append(idAttribute_).append("'>") // id='My_Heading'>
      .append(contents_)                                 // My Heading
      .append("</h").append(lvlStr).append(">\n");       // </h2>\n
    return hx;
}
