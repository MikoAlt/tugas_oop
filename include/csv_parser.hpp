//
// Created by Miko on 5/12/2025.
//

// A minimal CSV Parser, to be used by other classes

#ifndef CSVREADER_HPP
#define CSVREADER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>

using CsvRow = std::vector<std::string>;

class CsvReader {
public:
    explicit CsvReader(std::string  filename, char delimiter = ',');
    ~CsvReader() = default;

    CsvReader(const CsvReader&) = delete;
    CsvReader& operator=(const CsvReader&) = delete;
    CsvReader(CsvReader&&) = delete;
    CsvReader& operator=(CsvReader&&) = delete;

    bool isOpen() const;
    bool readRow(CsvRow& row);

private:
    std::string filename_;
    char        delimiter_;
    std::ifstream fileStream_;
    bool        isOpen_ = false;

    void parseLine(const std::string& line, CsvRow& row) const;
};

#endif // CSVREADER_HPP
