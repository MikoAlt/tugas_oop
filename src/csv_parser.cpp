//
// Created by Miko on 5/12/2025.
//

// A minimal csv parser, to be used by other classes

#include <csv_parser.hpp>

#include <sstream>
#include <iostream>
#include <utility>

CsvReader::CsvReader(std::string  filename, char delimiter)
    : filename_(std::move(filename)), delimiter_(delimiter)
{
    this->fileStream_.open(this->filename_);
    this->isOpen_ = this->fileStream_.is_open();

    if (!this->isOpen_) {
        throw std::runtime_error("CsvReader Error: Could not open file: " + this->filename_);
    }
}

bool CsvReader::isOpen() const {
    return this->isOpen_;
}

bool CsvReader::readRow(CsvRow& row) {
    row.clear();

    if (!this->isOpen_) { // If we manually closed it or it failed before
        return false;
    }

    // Check stream state *before* attempting to read.
    // If we're already at EOF or in an error state, don't proceed.
    if (this->fileStream_.eof() || !this->fileStream_.good()) {
        this->isOpen_ = false;
        return false;
    }

    std::string line;
    if (std::getline(this->fileStream_, line)) {
        // Successfully read a line.
        // An empty line at EOF is considered the end of readable content.
        if (line.empty() && this->fileStream_.eof()) {
            this->isOpen_ = false; // Mark as not open for further reads.
            return false;          // No valid row to parse from this.
        }

        this->parseLine(line, row);

        // After a successful read and parse, if the *next* read would fail due to EOF,
        // fileStream_.eof() will be true now. Update isOpen_ for future calls to isOpen().
        if (this->fileStream_.eof() || !this->fileStream_.good()) {
            this->isOpen_ = false;
        }
        return true;
    } else {
        // std::getline failed, meaning EOF was hit or another stream error occurred.
        this->isOpen_ = false;
        return false;
    }
}
void CsvReader::parseLine(const std::string& line, CsvRow& row) const {
    std::stringstream fieldBuilder;
    bool inQuotes = false;

    for (size_t i = 0; i < line.length(); ++i) {
        char currentChar = line[i];

        if (currentChar == '"') {
            if (!inQuotes) {
                if (fieldBuilder.tellp() == 0) {
                     inQuotes = true;
                } else {
                     fieldBuilder << currentChar;
                }
            } else {
                if (i + 1 < line.length() && line[i+1] == '"') {
                    fieldBuilder << '"';
                    i++;
                } else {
                    bool atEnd = (i + 1 == line.length());
                    bool followedByDelimiter = !atEnd && line[i+1] == this->delimiter_;

                    if (atEnd || followedByDelimiter) {
                         inQuotes = false;
                    } else {
                         fieldBuilder << currentChar;
                    }
                }
            }
        } else if (currentChar == this->delimiter_ && !inQuotes) {
            row.push_back(fieldBuilder.str());
            fieldBuilder.str("");
            fieldBuilder.clear();
        } else {
            fieldBuilder << currentChar;
        }
    }

    row.push_back(fieldBuilder.str());
}
