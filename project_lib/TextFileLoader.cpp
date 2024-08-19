#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include <vector>
#include "TextFileLoader.hpp"
#include "ContactRecord.hpp"

TextFileLoader::TextFileLoader(std::string filepath)
: filepath_{std::move(filepath)} {
}

bool TextFileLoader::process() {
    std::ifstream file;
    file.open(filepath_);
    if (file.fail()) {
        throw std::runtime_error{"FILE FAILURE: " + filepath_};
    }

    std::string lineContents;

    while (std::getline(file, lineContents)) {

        // Remove carriage return from end of line if file is CRLF
        if (lineContents[lineContents.size() - 1] == '\r') {
            lineContents.erase(lineContents.size() - 1);
        }

        // Delimiter sanity check to catch blank lines etc.
        if (lineContents.find(',') != std::string::npos) {
            std::string token;
            std::stringstream ss{lineContents};
            std::string tokens[5];
            for (auto &i: tokens) {
                std::getline(ss, token, ',');
                i = token;
            }
            contactRecords_.emplace_back(tokens);
        }
    }
    file.close();
    return true;
}

void TextFileLoader::setFilepath(std::string filepath) {
    filepath_ = std::move(filepath);
    contactRecords_.clear();
}

std::vector<ContactRecord> TextFileLoader::getContactRecords() {
    if (contactRecords_.empty()) process();
    return contactRecords_;
}
