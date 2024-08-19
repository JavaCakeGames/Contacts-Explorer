#ifndef CONTACTS_EXPLORER_CONTACTRECORD_HPP
#define CONTACTS_EXPLORER_CONTACTRECORD_HPP

#include <string>

/**
 * A contact record.
 */
class ContactRecord {

public:

    /** Default constructor; doesn't initialise data. */
    ContactRecord();

    /** Initialise a contact record with an array of tokens. In order:
     * <ul>
     * <li>ID (int)</li>
     * <li>First name (string)</li>
     * <li>Last name (string)</li>
     * <li>Email address (string)</li>
     * <li>Country (string - full name, not country code)</li>
     * </ul>*/
    explicit ContactRecord(std::string tokens[]);

    /** @return The contact record's ID. */
    int getId();

    /**
     * @param digits The number of digits to pad the string to.
     * @return The contact record's ID, as a string, padded with leading zeros.
     */
    std::string getPaddedId(unsigned digits);

    /**
     * Gets a padded ID.
     * This is more of a convenience function than to do with the record itself.
     * @param digits The number of digits to pad to.
     * @param id The ID to pad.
     * @return The padded ID as a string
     */
    std::string getPaddedId(unsigned digits, unsigned id);

    /** @return The person's first name as a string (e.g. Joe). */
    [[nodiscard]] std::string getFirstName() const;

    /** @return The person's last name as a string (e.g. Bloggs). */
    [[nodiscard]] std::string getLastName() const;

    /** @return The person's email address as a string (e.g. `joe@example.com`). */
    std::string getEmail();

    /** @return The person's country address as a string (e.g. United Kingdom). */
    std::string getCountry();

    /** @return The contact record as comma-separated values. */
    std::string getAsCsv();

    /** @return The contact record as plain text name-value pairs. */
    std::string getAsPlainText();

    /** Less-than operator used for case-insensitive sorting by last name then
     * first name. */
    bool operator < (ContactRecord& contactRecord) const;

private:
    int id_ {-1}; // Contact records with ID -1 are ignored
    std::string firstName_;
    std::string lastName_;
    std::string email_;
    std::string country_;

};

#endif //CONTACTS_EXPLORER_CONTACTRECORD_HPP
