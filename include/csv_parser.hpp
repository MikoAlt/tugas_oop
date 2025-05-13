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

/**
 * @class CsvReader
 * @brief A simple CSV file reader for parsing rows from a CSV file.
 *
 * The CsvReader class provides functionality to open and read rows from a CSV file,
 * using a specified delimiter (default is comma). It does not allow copy or move semantics.
 */
 
/**
 * @brief Constructs a CsvReader for the specified file and delimiter.
 * @param filename The path to the CSV file to read.
 * @param delimiter The character used to separate fields in the CSV file (default is ',').
 */
 
/**
 * @brief Checks if the CSV file is successfully opened.
 * @return true if the file is open, false otherwise.
 */
 
/**
 * @brief Reads the next row from the CSV file into the provided CsvRow object.
 * @param row Reference to a CsvRow object where the parsed data will be stored.
 * @return true if a row was successfully read, false if end of file or error.
 */
 
/**
 * @brief Parses a single line from the CSV file into a CsvRow object.
 * @param line The line from the CSV file to parse.
 * @param row Reference to a CsvRow object where the parsed data will be stored.
 */
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
