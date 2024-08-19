project(contacts_explorer)

set(HEADER_FILES
    ContactRecord.hpp TextFileLoader.hpp Website.hpp WebsiteSettings.hpp
    Element/Element.hpp Element/Container.hpp Element/Heading.hpp Element/Hyperlink.hpp Element/List.hpp Element/Table.hpp
    Page/Page.hpp Page/DetailsPage.hpp Page/IndexPage.hpp
)
set(SOURCE_FILES
    ContactRecord.cpp TextFileLoader.cpp Website.cpp WebsiteSettings.cpp
        Element/Element.cpp Element/Container.cpp Element/Heading.cpp Element/Hyperlink.cpp Element/List.cpp Element/Table.cpp
    Page/Page.cpp Page/DetailsPage.cpp Page/IndexPage.cpp
)

add_library(project_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})