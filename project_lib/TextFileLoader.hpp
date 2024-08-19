#ifndef CONTACTS_EXPLORER_TEXTFILELOADER_HPP
#define CONTACTS_EXPLORER_TEXTFILELOADER_HPP

#include <string>
#include <vector>
#include "ContactRecord.hpp"

/** Loads a text file from disk. */
class TextFileLoader {

public:

    /**`TextFileLoader` constructor.
     * @param filepath The filepath of the text file to load.
     */
    explicit TextFileLoader(std::string filepath);

    /** Load and process the text file.
     * @return true if successful.
     * */
    bool process();

    /** Change the filepath. This clears all contact records from memory.
     * @param filepath
     */
    void setFilepath(std::string filepath);

    /**
     * Get all contact records within the text file.
     * @return Vector of `ContactRecords`.
     */
    std::vector<ContactRecord> getContactRecords();

private:
    std::string filepath_;
    std::vector<ContactRecord> contactRecords_;

};

#endif //CONTACTS_EXPLORER_TEXTFILELOADER_HPP
