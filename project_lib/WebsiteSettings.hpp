#ifndef CONTACTS_EXPLORER_WEBSITESETTINGS_CPP
#define CONTACTS_EXPLORER_WEBSITESETTINGS_CPP

#include <string>

/**
 * Provides various customisation options for the generated website.
 */
class WebsiteSettings {

public:

    /** Website settings constructor. Mandatory for website.
     * Directories should always end in a slash.
     * @param in Absolute path where contacts data etc. is read from
     * @param out Absolute path where generated website is output
     */
    WebsiteSettings(std::string in, std::string out);

    /** Settings for the index page only. */
    struct IndexSettings {
        /** True if the anchor selector in the bottom-left should be present. */
        bool enableAnchors = true;

        /** Whether the initial headings and anchor links should be uppercase
         * or lowercase. */
        bool capitalInitials = true;

        /** The heading and anchor string used for names that don't begin with
         * letters in the latin alphabet. */
        std::string omega = "Ω";

        /** The title to be displayed in the browser tab. */
        std::string title = "Index Page";
    };

    /** Settings for the details pages only. */
    struct DetailsSettings {
        /** Whether the Previous/Next Name links should be present. */
        bool enablePrevNextName = true;

        /** Whether the Previous/Next ID links should be present.
         * This should be set to false if IDs are non-sequential. */
        bool enablePrevNextId = true;

        /** Whether the Random link should be present.
         * This should be set to false if IDs are non-sequential. */
        bool enableRandom = true;

        /** The part of the filename before the ID. */
        std::string prefix = "details-";

        /** The part of the filename after the ID. */
        std::string suffix = ".html";
    };

    /** Templates to search for in `index.html` and replace with the respective
     * content. */
    struct TemplateSettings {
        std::string main = "$mainContent";
        std::string title = "$title";
    };

    struct WebsiteSettings::IndexSettings index;
    struct WebsiteSettings::DetailsSettings details;
    struct WebsiteSettings::TemplateSettings templateSettings;

    // Paths must have trailing slashes if they are directories
    std::string inPath;
    std::string outPath;

private:

};

#endif //CONTACTS_EXPLORER_WEBSITESETTINGS_CPP
