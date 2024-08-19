#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <filesystem>
#include "doctest.h"
#include "Element/Hyperlink.hpp"
#include "Element/Heading.hpp"
#include "Element/Container.hpp"
#include "Element/List.hpp"
#include "Element/Table.hpp"
#include "WebsiteSettings.hpp"
#include "ContactRecord.hpp"
#include "TextFileLoader.hpp"
#include "Website.hpp"

/** Test if creating a `<div>` element works. */
TEST_CASE("create div") {
    Container container;
    container.add("Hello!");

    std::string expected = "<div>\nHello!\n</div>\n";
    std::string actual = container.toString();
    CHECK(expected == actual);
}

/** Test if creating a `<span>` element works. */
TEST_CASE("create span") {
    Container container(Container::Types::SPAN);
    container.add("Hello!");

    std::string expected = "<span>\nHello!\n</span>\n";
    std::string actual = container.toString();
    CHECK(expected == actual);
}

/** Test if creating `<h1>` through `<h6>` works. */
TEST_CASE("create headings") {
    for (int level = 1; level <= 6; level++) {
        Heading heading(level, "Cool Heading");

        std::string expected;
        expected.append("\n<h").append(std::to_string(level))
                .append(" id='Cool Heading'>Cool Heading</h")
                .append(std::to_string(level)).append(">\n");
        std::string actual = heading.toString();
        CHECK(actual == expected);
    }
}

/** Test if creating an `<a>` element works. */
TEST_CASE("create a") {
    Hyperlink hyperlink("https://duckduckgo.com/");

    std::string expected =
            "<a href='https://duckduckgo.com/'>https://duckduckgo.com/</a>\n";
    std::string actual = hyperlink.toString();
    CHECK(actual == expected);
}

/** Test if creating a `<ul>` element works.
 * **Acceptance test 4.** */
TEST_CASE("create ul") {
    List list;
    list.addItem("item 1")
        .addItem("item 2");

    std::string expected =
            "<ul>\n<li>\n\titem 1</li>\n<li>\n\titem 2</li>\n</ul>\n";
    std::string actual = list.toString();
    CHECK(actual == expected);
}

/** Test if creating an `<ol>` element works. */
TEST_CASE("create ol") {
    List list(true);
    list.addItem("item 1")
        .addItem("item 2");

    std::string expected =
            "<ol>\n<li>\n\titem 1</li>\n<li>\n\titem 2</li>\n</ol>\n";
    std::string actual = list.toString();
    CHECK(actual == expected);
}

/** Test if creating a `<table>` element works. */
TEST_CASE("create table") {
    Table table;
    std::vector<std::string> columns = {"col1", "col2"};
    table.addRow(columns)
         .addRow(columns);

    std::string expected;
    expected.append("<table>\n")
            .append("<tr>\n<th>col1</th>\n<th>col2</th>\n</tr>\n")
            .append("<tr>\n<td>col1</td>\n<td>col2</td>\n</tr>\n")
            .append("</table>\n");
    std::string actual = table.toString();
    CHECK(expected == actual);
}

/** Test if the website settings can be altered.
 * **Acceptance test 1.** */
TEST_CASE("alter settings") {
    WebsiteSettings settings("in", "out");
    settings.index.enableAnchors = false;
    settings.details.prefix = "user-";
    settings.templateSettings.main = "%%MAIN%%";

    CHECK(settings.inPath == "in");
    CHECK(settings.outPath == "out");
    CHECK(!settings.index.enableAnchors);
    CHECK(settings.details.prefix == "user-");
    CHECK(settings.templateSettings.main == "%%MAIN%%");
}

/** Test if creating a contact record sets its details correctly. */
TEST_CASE("create contact record") {
    std::string tokens[5] =
            {"50", "Joe", "Bloggs", "joe@example.com", "United Kingdom"};
    ContactRecord contact(tokens);
    CHECK(contact.getId() == 50);
    CHECK(contact.getFirstName() == "Joe");
    CHECK(contact.getLastName() == "Bloggs");
    CHECK(contact.getEmail() == "joe@example.com");
    CHECK(contact.getCountry() == "United Kingdom");
}

/** Test if the correct number of contact records are obtained from the CSV
 * file. **Acceptance test 2.** */
TEST_CASE("obtain records") {
    WebsiteSettings settings(
            "/home/student/clionprojects/contacts-explorer/resources/",
            "/var/www/localhost/htdocs/"
    );
    TextFileLoader textFileLoader{settings.inPath + "contacts.csv"};
    auto records = textFileLoader.getContactRecords();
    CHECK(records.size() == 1000);
}

/** Test if writing to disk manages to create `index.html`.
 * **Acceptance test 3.** */
TEST_CASE("write to disk") {
    WebsiteSettings settings(
            "/home/student/clionprojects/contacts-explorer/resources/",
            "/var/www/localhost/htdocs/"
    );
    Website website(settings);
    website.writeToDisk();
    CHECK(std::filesystem::exists(settings.outPath + "index.html"));
}
