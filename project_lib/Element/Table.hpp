#ifndef CONTACTS_EXPLORER_TABLE_HPP
#define CONTACTS_EXPLORER_TABLE_HPP

#include "Element.hpp"

#include <vector>

/**
 * A table element - `<table>`.
 * Table elements (`<tr>`, `<th>`, `<td>`) are also handled by this class.
 */
class Table : public Element {

public:

    /** Creates a table where each column has a heading. */
    Table();

    /** Creates a table.
     * @param rowHeadings True if each row should have a heading;
     *                    false for columns.
     */
    explicit Table(bool rowHeadings);

    /** Adds a single row to the table.
     * @param columns A vector of columns as strings.
     *                Each string may contain HTML.
     * @return Self as a pointer for chaining.
     */
    Table& addRow(const std::vector<std::string>& columns);

    /** @return The table as a string. */
    std::string toString() override;

private:
    std::vector<std::vector<std::string>> rows_;

    bool rowHeadings_ = false; // If each row has a heading, instead of each column
};

#endif //CONTACTS_EXPLORER_TABLE_HPP
