#include "WebsiteSettings.hpp"

#include <utility>

WebsiteSettings::WebsiteSettings(std::string in, std::string out)
: inPath{std::move(in)}, outPath{std::move(out)} {

}
