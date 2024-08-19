#include <iostream>
#include <algorithm>
#include "ContactRecord.hpp"

ContactRecord::ContactRecord() {

}

ContactRecord::ContactRecord(std::string* tokens) :
id_{std::stoi(tokens[0])},
firstName_{tokens[1]},
lastName_{tokens[2]},
email_{tokens[3]},
country_{tokens[4]} {

}

int ContactRecord::getId() {
    return id_;
}

std::string ContactRecord::getPaddedId(unsigned digits) {
    return getPaddedId(digits, id_);
}

std::string ContactRecord::getPaddedId(unsigned int digits, unsigned int id) {

    if (digits > 64) { // Failsafe in case of incorrect argument order
        throw std::invalid_argument{"ID cannot be padded to over 64 digits."};
    }

    std::string idAsString = std::to_string(id);
    const auto idLength = idAsString.length();
    if (idLength < digits) {
        idAsString.insert(0, digits - idLength, '0');
    } else if (idLength > digits) {
        std::cout << "WARNING: Cannot pad ID " << id_
                  << " to " << digits << " digits.\n";
    }
    return idAsString;
}

std::string ContactRecord::getFirstName() const {
    return firstName_;
}

std::string ContactRecord::getLastName() const {
    return lastName_;
}

std::string ContactRecord::getEmail() {
    return email_;
}

std::string ContactRecord::getCountry() {
    return country_;
}

std::string ContactRecord::getAsCsv() {
    std::string csv;
    csv.append(std::to_string(id_)).append(",")
            .append(firstName_).append(",")
            .append(lastName_).append(",")
            .append(email_).append(",")
            .append(country_).append("\n");
    return csv;
}

std::string ContactRecord::getAsPlainText() {
    std::string txt;
    txt.append("ID: ").append(std::to_string(id_)).append("\n");
    txt.append("First name: ").append(firstName_).append("\n");
    txt.append("Last name: ").append(lastName_).append("\n");
    txt.append("Email address: ").append(email_).append("\n");
    txt.append("Country: ").append(country_).append("\n");
    return txt;
}

bool ContactRecord::operator < (ContactRecord& contactRecord) const {
    // Convert to lowercase for case-insensitive comparison
    std::string record1, record2;
    record1.append(lastName_).append(firstName_);
    std::transform(record1.begin(), record1.end(), record1.begin(), ::tolower);
    record2.append(contactRecord.getLastName())
           .append(contactRecord.getFirstName());
    std::transform(record2.begin(), record2.end(), record2.begin(), ::tolower);
    return record1 < record2;
}
