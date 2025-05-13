//
// Created by Miko on 5/13/2025.
//

#include "gtest/gtest.h"
#include "dataset_loader.hpp"
#include "city.hpp"
#include <fstream>
#include <vector>
#include <string>
#include <cstdio> // For std::remove

// Re-use helper from CsvReaderTest or define it here
std::string create_temp_csv_loader_file(const std::string& content, const std::string& filename_prefix = "test_loader_csv_") {
    static int counter_loader = 0;
    std::string filename = filename_prefix + std::to_string(counter_loader++) + ".csv";
    std::ofstream outfile(filename);
    if (!outfile) {
        throw std::runtime_error("Failed to create temp file: " + filename);
    }
    outfile << content;
    outfile.close();
    return filename;
}

class DatasetLoaderTest : public ::testing::Test {
protected:
    std::vector<std::string> temp_files_;

    void TearDown() override {
        for (const auto& file : temp_files_) {
            std::remove(file.c_str());
        }
        temp_files_.clear();
    }

    std::string make_temp_file(const std::string& content) {
        std::string filename = create_temp_csv_loader_file(content);
        temp_files_.push_back(filename);
        return filename;
    }
};

TEST_F(DatasetLoaderTest, LoadValidData) {
    std::string content =
        "city,city_ascii,lat,lng,country,iso2,iso3,admin_name,capital,population,id\n"
        "Tokyo,Tokyo,35.6897,139.6922,Japan,JP,JPN,Tokyo,primary,37435191,1392685764\n"
        "Delhi,Delhi,28.6139,77.2090,India,IN,IND,Delhi,admin,29399141,1356872604\n";
    std::string filename = make_temp_file(content);

    DatasetLoader loader(filename);
    std::vector<City> cities;
    ASSERT_NO_THROW(cities = loader.loadAndParseCities());

    ASSERT_EQ(cities.size(), 2);
    EXPECT_EQ(cities[0].name, "Tokyo");
    EXPECT_EQ(cities[0].country, "Japan");
    EXPECT_DOUBLE_EQ(cities[0].lat, 35.6897);
    EXPECT_DOUBLE_EQ(cities[0].lng, 139.6922);
    EXPECT_EQ(cities[0].population, 37435191);

    EXPECT_EQ(cities[1].name, "Delhi");
    EXPECT_EQ(cities[1].country, "India");
    EXPECT_EQ(cities[1].population, 29399141);
}

TEST_F(DatasetLoaderTest, SkipRowMissingPopulation) {
    std::string content =
        "city,city_ascii,lat,lng,country,iso2,iso3,admin_name,capital,population,id\n"
        "ValidCity,ValidCity,10.0,20.0,CountryA,CA,CAA,,,1000,1\n"
        "NoPopCity,NoPopCity,12.0,22.0,CountryB,CB,CBB,,,,2\n"; // Missing population
    std::string filename = make_temp_file(content);
    DatasetLoader loader(filename);
    std::vector<City> cities = loader.loadAndParseCities();
    ASSERT_EQ(cities.size(), 1);
    EXPECT_EQ(cities[0].name, "ValidCity");
}

TEST_F(DatasetLoaderTest, SkipRowInvalidPopulation) {
    std::string content =
        "city,city_ascii,lat,lng,country,iso2,iso3,admin_name,capital,population,id\n"
        "ValidCity,ValidCity,10.0,20.0,CountryA,CA,CAA,,,1000,1\n"
        "BadPopCity,BadPopCity,12.0,22.0,CountryB,CB,CBB,,,NOT_A_NUMBER,2\n";
    std::string filename = make_temp_file(content);
    DatasetLoader loader(filename);
    std::vector<City> cities = loader.loadAndParseCities();
    ASSERT_EQ(cities.size(), 1);
    EXPECT_EQ(cities[0].name, "ValidCity");
}


TEST_F(DatasetLoaderTest, SkipRowInsufficientColumns) {
    std::string content =
        "city,city_ascii,lat,lng,country,iso2,iso3,admin_name,capital,population,id\n"
        "ValidCity,ValidCity,10.0,20.0,CountryA,CA,CAA,,1000,1\n"
        "ShortRow,ShortRow,5.0,5.0,CountryC\n"; // Only 5 columns
    std::string filename = make_temp_file(content);
    DatasetLoader loader(filename);
    std::vector<City> cities = loader.loadAndParseCities();
    ASSERT_EQ(cities.size(), 1);
    EXPECT_EQ(cities[0].name, "ValidCity");
}

TEST_F(DatasetLoaderTest, SkipRowInvalidLatOrLng) {
    std::string content =
        "city,city_ascii,lat,lng,country,iso2,iso3,admin_name,capital,population,id\n"
        "BadLat,BadLat,NOT_LAT,20.0,CountryD,CD,CDD,,100,3\n"
        "BadLng,BadLng,10.0,NOT_LNG,CountryE,CE,CEE,,200,4\n"
        "Valid,Valid,30.0,40.0,CountryF,CF,CFF,,300,5\n";
    std::string filename = make_temp_file(content);
    DatasetLoader loader(filename);
    std::vector<City> cities = loader.loadAndParseCities();
    ASSERT_EQ(cities.size(), 1);
    EXPECT_EQ(cities[0].name, "Valid");
}

TEST_F(DatasetLoaderTest, HandleEmptyFile) {
    std::string filename = make_temp_file(""); // Empty file
    DatasetLoader loader(filename);
    std::vector<City> cities = loader.loadAndParseCities();
    EXPECT_TRUE(cities.empty());
}

TEST_F(DatasetLoaderTest, HandleFileWithOnlyHeader) {
    std::string content = "city,city_ascii,lat,lng,country,iso2,iso3,admin_name,capital,population,id\n";
    std::string filename = make_temp_file(content);
    DatasetLoader loader(filename);
    std::vector<City> cities = loader.loadAndParseCities();
    EXPECT_TRUE(cities.empty());
}