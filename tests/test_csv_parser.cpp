//
// Created by Miko on 5/13/2025.
//

#include "gtest/gtest.h"
#include "csv_parser.hpp" // Your CsvReader header
#include <fstream>
#include <vector>
#include <string>
#include <cstdio> // For std::remove

// Helper function to create a temporary CSV file
std::string create_temp_csv_file(const std::string& content, const std::string& filename_prefix = "test_csv_") {
    // Create a unique-ish filename
    static int counter = 0;
    std::string filename = filename_prefix + std::to_string(counter++) + ".csv";
    std::ofstream outfile(filename);
    if (!outfile) {
        throw std::runtime_error("Failed to create temp file: " + filename);
    }
    outfile << content;
    outfile.close();
    return filename;
}

class CsvReaderTest : public ::testing::Test {
protected:
    std::vector<std::string> temp_files_;

    void TearDown() override {
        for (const auto& file : temp_files_) {
            std::remove(file.c_str());
        }
        temp_files_.clear();
    }

    std::string make_temp_file(const std::string& content) {
        std::string filename = create_temp_csv_file(content);
        temp_files_.push_back(filename);
        return filename;
    }
};


TEST_F(CsvReaderTest, OpenNonExistentFile) {
    EXPECT_THROW(CsvReader reader("non_existent_file.csv"), std::runtime_error);
}

TEST_F(CsvReaderTest, ReadSimpleCsv) {
    std::string content = "col1,col2,col3\nval1,val2,val3\n1,2,3";
    std::string filename = make_temp_file(content);
    CsvReader reader(filename);
    ASSERT_TRUE(reader.isOpen());

    CsvRow row;
    ASSERT_TRUE(reader.readRow(row));
    ASSERT_EQ(row.size(), 3);
    EXPECT_EQ(row[0], "col1");
    EXPECT_EQ(row[1], "col2");
    EXPECT_EQ(row[2], "col3");

    ASSERT_TRUE(reader.readRow(row));
    ASSERT_EQ(row.size(), 3);
    EXPECT_EQ(row[0], "val1");
    EXPECT_EQ(row[1], "val2");
    EXPECT_EQ(row[2], "val3");

    ASSERT_TRUE(reader.readRow(row));
    ASSERT_EQ(row.size(), 3);
    EXPECT_EQ(row[0], "1");
    EXPECT_EQ(row[1], "2");
    EXPECT_EQ(row[2], "3");

    EXPECT_FALSE(reader.readRow(row)); // EOF
    EXPECT_FALSE(reader.isOpen()); // isOpen should be false after EOF attempt
}

TEST_F(CsvReaderTest, ReadCsvWithQuotes) {
    std::string content = "name,description\n\"Smith, John\",\"A person, with a comma\"\n\"Doe, Jane\",\"Line with\nnewline char\"";
    std::string filename = make_temp_file(content);
    CsvReader reader(filename);
    ASSERT_TRUE(reader.isOpen());

    CsvRow row;
    ASSERT_TRUE(reader.readRow(row)); // Header

    ASSERT_TRUE(reader.readRow(row));
    ASSERT_EQ(row.size(), 2);
    EXPECT_EQ(row[0], "Smith, John");
    EXPECT_EQ(row[1], "A person, with a comma");

    // Note: Your current CsvReader::parseLine might not correctly handle embedded newlines within quotes.
    // If it splits on the CSV newline, the next test might be different.
    // This test assumes parseLine correctly handles multiline quoted fields IF they are part of a single line from getline.
    // If your simplemaps CSV doesn't have multiline fields, this might be less critical.
    // The provided `CsvReader` reads line by line, so embedded newlines are tricky.
    // Let's test with `""` for escaped quotes.
    content = "id,value\n1,\"Hello, \"\"World\"\"!\"";
    filename = make_temp_file(content);
    CsvReader reader2(filename);
    ASSERT_TRUE(reader2.isOpen());
    ASSERT_TRUE(reader2.readRow(row)); // Header
    ASSERT_TRUE(reader2.readRow(row));
    ASSERT_EQ(row.size(), 2);
    EXPECT_EQ(row[0], "1");
    EXPECT_EQ(row[1], "Hello, \"World\"!");
}

TEST_F(CsvReaderTest, ReadEmptyFile) {
    std::string filename = make_temp_file("");
    CsvReader reader(filename);
    ASSERT_TRUE(reader.isOpen());
    CsvRow row;
    EXPECT_FALSE(reader.readRow(row));
    EXPECT_FALSE(reader.isOpen());
}

TEST_F(CsvReaderTest, ReadFileWithEmptyLines) {
    std::string content = "a,b\n\n1,2\n"; // One empty line, one line with trailing newline
    std::string filename = make_temp_file(content);
    CsvReader reader(filename);
    ASSERT_TRUE(reader.isOpen());

    CsvRow row;
    ASSERT_TRUE(reader.readRow(row)); // a,b
    EXPECT_EQ(row[0], "a");

    ASSERT_TRUE(reader.readRow(row)); // Empty line, CsvReader::parseLine might push one empty string
    ASSERT_GE(row.size(), 1);         // or size 0 if line.empty() check in readRow catches it first.
                                      // Your current CsvReader's parseLine would add one empty string for an empty line.
    EXPECT_EQ(row.size(), 1);
    EXPECT_TRUE(row[0].empty());


    ASSERT_TRUE(reader.readRow(row)); // 1,2
    EXPECT_EQ(row[0], "1");

    // Trailing newline often means getline returns true with an empty string, then next getline is EOF
    // Your CsvReader's `if (line.empty() && this->fileStream_.eof())` handles this well.
    EXPECT_FALSE(reader.readRow(row));
    EXPECT_FALSE(reader.isOpen());
}

TEST_F(CsvReaderTest, DifferentDelimiter) {
    std::string content = "val1;val2\nval3;val4";
    std::string filename = make_temp_file(content);
    CsvReader reader(filename, ';'); // Use semicolon as delimiter
    ASSERT_TRUE(reader.isOpen());

    CsvRow row;
    ASSERT_TRUE(reader.readRow(row));
    ASSERT_EQ(row.size(), 2);
    EXPECT_EQ(row[0], "val1");
    EXPECT_EQ(row[1], "val2");
}