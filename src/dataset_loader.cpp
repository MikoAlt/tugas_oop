#include <dataset_loader.hpp> // Class declaration
#include <sstream>      // For std::stringstream, std::stod, std::stol
#include <stdexcept>    // For std::runtime_error, std::invalid_argument, std::out_of_range
#include <iostream>     // For std::cerr (error reporting for skipped rows)
#include <utility>

DatasetLoader::DatasetLoader(std::string  csv_filepath)
    : filepath_(std::move(csv_filepath)) {} // Initializer list is idiomatic for constructors

std::vector<City> DatasetLoader::loadAndParseCities() {
    std::vector<City> cities;
    // CsvReader constructor throws std::runtime_error if file can't be opened
    CsvReader reader(this->filepath_);

    // Skip header row
    CsvRow header_row;
    if (!reader.readRow(header_row)) {
        // File is empty or header couldn't be read
        std::cerr << "Warning: CSV file '" << this->filepath_ << "' is empty or header could not be read." << std::endl;
        return cities; // Return empty vector
    }

    CsvRow current_csv_row;
    unsigned int line_number = 1; // Start counting after header

    while (reader.readRow(current_csv_row)) {
        line_number++;

        // Check if the row has enough columns to access all required fields
        if (current_csv_row.size() < EXPECTED_MIN_COLUMNS) {
            // std::cerr << "Warning (Line " << line_number << "): Skipping row due to insufficient columns. Expected at least "
                      // << EXPECTED_MIN_COLUMNS << ", got " << current_csv_row.size() << "." << std::endl;
            continue;
        }

        // Requirement: Skip rows with missing population.
        // The population field is at COL_POPULATION.
        const std::string& population_str = current_csv_row[COL_POPULATION];
        if (population_str.empty()) {
//            std::cerr << "Info (Line " << line_number << "): Skipping row due to missing (empty) population data." << std::endl;
            continue;
        }


        try {
            City city_obj;
            // Population (must be valid, otherwise skip)
            try {
                city_obj.population = std::stol(population_str);
                // Optionally, one could also skip if population is <= 0, if that's considered invalid/missing.
            } catch (const std::invalid_argument&) {
//                std::cerr << "Info (Line " << line_number << "): Skipping row due to non-numeric population: '" << population_str << "'." << std::endl;
                continue; // Skip row as population is not a valid number
            } catch (const std::out_of_range&) {
//                std::cerr << "Info (Line " << line_number << "): Skipping row due to out-of-range population: '" << population_str << "'." << std::endl;
                continue; // Skip row as population number is too large/small for long
            }

            // If population is valid, proceed to parse other fields.
            // If other fields are invalid, we will also skip the row for data integrity.
            city_obj.name = current_csv_row[DatasetLoader::COL_CITY_ASCII];
            city_obj.country = current_csv_row[DatasetLoader::COL_COUNTRY];

            const std::string& lat_str = current_csv_row[DatasetLoader::COL_LAT];
            const std::string& lng_str = current_csv_row[DatasetLoader::COL_LNG];

            if (lat_str.empty() || lng_str.empty()) {
//                std::cerr << "Info (Line " << line_number << "): Skipping row due to missing latitude or longitude." << std::endl;
                continue;
            }

            try {
                city_obj.lat = std::stod(lat_str);
            } catch (const std::invalid_argument&) {
                // std::cerr << "Info (Line " << line_number << "): Skipping row due to invalid latitude: '" << lat_str << "'." << std::endl;
                continue;
            } catch (const std::out_of_range&) {
                // std::cerr << "Info (Line " << line_number << "): Skipping row due to out-of-range latitude: '" << lat_str << "'." << std::endl;
                continue;
            }

            try {
                city_obj.lng = std::stod(lng_str);
            } catch (const std::invalid_argument&) {
                // std::cerr << "Info (Line " << line_number << "): Skipping row due to invalid longitude: '" << lng_str << "'." << std::endl;
                continue;
            } catch (const std::out_of_range&) {
                // std::cerr << "Info (Line " << line_number << "): Skipping row due to out-of-range longitude: '" << lng_str << "'." << std::endl;
                continue;
            }

            // If all necessary fields are parsed successfully
            cities.push_back(city_obj);

        } catch (const std::out_of_range& oor_idx) {
            // This primarily catches potential out_of_range from std::stod/std::stol,
            // as vector operator[] itself doesn't throw this.
            // The size check above prevents vector access issues.
            // std::cerr << "Error (Line " << line_number << "): Skipping row due to unexpected out-of-range issue during parsing. "
                      // << oor_idx.what() << std::endl;
            continue;
        }
    }

    std::cout << "Info: Successfully parsed " << cities.size() << " cities from '" << this->filepath_ << "'." << std::endl;
    return cities;
}