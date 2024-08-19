#include "Table.hpp"

Table::Table() {

}

Table::Table(bool rowHeadings) : rowHeadings_{rowHeadings} {

}


std::string Table::toString() {
    std::string html;
    html.append("<table>\n");
    for (unsigned y = 0; y < rows_.size(); y++) {
        html.append("<tr>\n");
        for (unsigned x = 0; x < rows_[y].size(); x++) {
            bool heading = (rowHeadings_ && (x == 0)) || (!rowHeadings_ && (y == 0));
            html.append(heading ? "<th>" : "<td>");
            html.append(rows_[y][x]);
            html.append(heading ? "</th>\n" : "</td>\n");
        }
        html.append("</tr>\n");
    }
    html.append("</table>\n");

    return html;
}

Table& Table::addRow(const std::vector<std::string>& columns) {
    rows_.emplace_back(columns);
    return *this;
}

