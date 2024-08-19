#include <iostream>
#include <chrono>
#include <iomanip>

#include "project_lib/WebsiteSettings.hpp"
#include "project_lib/Website.hpp"
#include "project_lib/TextFileLoader.hpp"
#include "AcceptanceTesting.hpp"

namespace Testing {

    const bool TESTING_MODE = false;

    void runAll(const WebsiteSettings& settings) {
        AcceptanceTesting acceptanceTesting(settings);
        acceptanceTesting.readTextFile();
        acceptanceTesting.displayAllContacts();
        acceptanceTesting.displaySingleRecord();
        acceptanceTesting.displayIndexSource();
        acceptanceTesting.addElementsToIndex();
        acceptanceTesting.displayDetailsSource();
        acceptanceTesting.addElementsToDetails();
        acceptanceTesting.generateAndSaveWebsite();
    }

}

int main() {

    auto start = std::chrono::high_resolution_clock::now();

    WebsiteSettings settings(
        //"/home/user/clionprojects/contacts-explorer/resources/",
        //"/var/www/localhost/htdocs/"
        R"(C:\Users\James\jcake\contacts-explorer\resources\)",
        R"(C:\Users\James\jcake\contacts-explorer\html\)"
    );
    Website website(settings);

    if (Testing::TESTING_MODE) {
        Testing::runAll(settings);
    } else {
        TextFileLoader textFileLoader{settings.inPath.append("contacts.csv")};
        auto records = textFileLoader.getContactRecords();

        website.addContactRecords(records);

        website.writeToDisk();
    }

    auto end = std::chrono::high_resolution_clock::now();
    float elapsed = std::chrono::duration<float>(end - start).count();
    // Display to 3 decimal places (millisecond precision)
    std::cout << "Website generated in " << std::fixed << std::setprecision(3)
              << elapsed << " seconds.\n";

    return 0; // Hoorah! We made it without a segfault (139)
}