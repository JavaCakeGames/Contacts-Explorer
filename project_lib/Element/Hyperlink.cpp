#include "Hyperlink.hpp"

#include <utility>

// See Hyperlinks.hpp for constructors due to template usage

Hyperlink::Hyperlink(std::string url)
: url_{url} {
    // If anchor, remove hash from contents
    if (url[0] == '#') url.erase(0, 1);
    contents_ = url;
}

Hyperlink::Hyperlink(std::string url, std::string contents)
: url_{std::move(url)}, contents_{std::move(contents)} {

}

Hyperlink::Hyperlink(std::string url, std::string contents, bool newTab)
: url_{std::move(url)}, contents_{std::move(contents)}, newTab_{newTab} {

}

std::string Hyperlink::toString() {
    std::string a = {};
    a.append("<a href='").append(url_).append("'");
    if (newTab_) a.append(" target='_blank'");
    a.append(">").append(contents_).append("</a>\n");
    return a;
}
