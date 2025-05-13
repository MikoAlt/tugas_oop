//
// Created by Miko on 5/13/2025.
//

#ifndef DATASET_LOADER_HPP
#define DATASET_LOADER_HPP

#include <string>
#include <vector>
#include <city.hpp>        // Definition of the City struct
#include <csv_parser.hpp>  // Your CsvReader class

class DatasetLoader {
public:
    // Constructor: takes the path to the CSV file.
    explicit DatasetLoader(std::string  csv_filepath);

    // Main method to load data from the CSV file.
    // It reads rows, parses them into City objects,
    // and skips rows with missing population data as required.
    // Throws std::runtime_error if the file cannot be opened or critical parsing fails.
    std::vector<City> loadAndParseCities();

private:
    std::string filepath_;

    // city,city_ascii,lat,lng,country,iso2,iso3,admin_name,capital,population,id
    // We'll use 'city_ascii' for name as it's often cleaner.
    // The data type is size_t to make it platform independent
    static const size_t COL_CITY_ASCII = 1; // For City::name
    static const size_t COL_LAT        = 2; // For City::lat
    static const size_t COL_LNG        = 3; // For City::lng
    static const size_t COL_COUNTRY    = 4; // For City::country
    static const size_t COL_POPULATION = 9; // For City::population

    // Expected number of columns in a valid data row.
    // Used to quickly skip malformed rows.
    static const size_t EXPECTED_MIN_COLUMNS = 10; // Need at least up to population column
};

#endif // DATASET_LOADER_HPP