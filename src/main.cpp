#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <iomanip>
#include <random>
#include <optional>
#include <functional>
#include <map>


#include <cli_parser.hpp>
#include <dataset_loader.hpp>
#include <city.hpp>
#include <sorter.hpp>
#include <sorter_factory.hpp>

const std::string DEFAULT_CSV_PATH = "worldcities.csv"; // Default path to the dataset

// Define a type alias for the function that generates a specific field comparator
using FieldComparatorGenerator = std::function<Sorter::Comparator(bool)>;

// Static map to hold the registry of key strings to their comparator generators
static const std::map<std::string, FieldComparatorGenerator> comparator_registry = {
    {"name", [](bool reverse_order) -> Sorter::Comparator {
        return [reverse_order](const City& a, const City& b) {
            return reverse_order ? (b.name < a.name) : (a.name < b.name);
        };
    }},
    {"country", [](bool reverse_order) -> Sorter::Comparator {
        return [reverse_order](const City& a, const City& b) {
            return reverse_order ? (b.country < a.country) : (a.country < b.country);
        };
    }},
    {"population", [](bool reverse_order) -> Sorter::Comparator {
        return [reverse_order](const City& a, const City& b) {
            return reverse_order ? (b.population < a.population) : (a.population < b.population);
        };
    }},
    {"lat", [](bool reverse_order) -> Sorter::Comparator {
        return [reverse_order](const City& a, const City& b) {
            return reverse_order ? (b.lat < a.lat) : (a.lat < b.lat);
        };
    }},
    {"lng", [](bool reverse_order) -> Sorter::Comparator {
        return [reverse_order](const City& a, const City& b) {
            return reverse_order ? (b.lng < a.lng) : (a.lng < b.lng);
        };
    }}
};

Sorter::Comparator createComparator(const std::string& key, bool reverse_order) {
    auto it = comparator_registry.find(key);
    if (it != comparator_registry.end()) {
        return it->second(reverse_order);
    } else {
        throw std::invalid_argument("Error: Unknown sort key specified for comparator: " + key);
    }
}

// --- Helper Function to Print Cities ---
void printCities(const std::vector<City>& cities, const std::optional<int>& limit_n_opt) {
    size_t limit = cities.size();
    if (limit_n_opt.has_value() && limit_n_opt.value() > 0) {
        limit = std::min(cities.size(), static_cast<size_t>(limit_n_opt.value()));
    } else if (limit_n_opt.has_value() && limit_n_opt.value() <= 0) {
        // If -n 0 or negative was somehow passed (though CLI parser should prevent <=0)
        return; // Print nothing
    }


    if (limit == 0 && !cities.empty()) {
        if (limit_n_opt.has_value()) return; // If -n was specified as 0, print nothing
    }

    std::cout << "\n--- Sorted Cities (First " << limit << " of " << cities.size() << " total rows) ---" << std::endl;
    std::cout << std::left << std::setw(30) << "City Name"
              << std::setw(25) << "Country"
              << std::setw(15) << "Population"
              << std::setw(15) << "Latitude"
              << std::setw(15) << "Longitude" << std::endl;
    std::cout << std::string(100, '-') << std::endl;

    for (size_t i = 0; i < limit; ++i) {
        const auto& city = cities[i];
        std::cout << std::left << std::setw(30) << city.name.substr(0, 28)
                  << std::setw(25) << city.country.substr(0, 23)
                  << std::right << std::setw(14) << city.population << " "
                  << std::fixed << std::setprecision(6) << std::setw(14) << city.lat << " "
                  << std::fixed << std::setprecision(6) << std::setw(14) << city.lng << std::endl;
    }
    if (cities.size() > limit && limit > 0) { // only print if some were shown
        std::cout << "... and " << (cities.size() - limit) << " more rows not shown." << std::endl;
    } else if (limit == 0 && !cities.empty() && limit_n_opt.has_value()) {
        std::cout << "(Printing 0 rows as requested by -n " << limit_n_opt.value() << ")" << std::endl;
    } else if (cities.empty()){
        std::cout << "(No cities to print)" << std::endl;
    }
    std::cout << std::string(100, '-') << std::endl;
}


void run_single_sort(const CliParser& cli_parser) {
    const std::string& algorithm_name = cli_parser.getAlgorithm();
    const std::string& sort_key = cli_parser.getKey();
    bool reverse_order = cli_parser.isReverseOrder();
    std::optional<int> limit_rows_opt = cli_parser.getLimitRows();

    std::cout << "Selected Algorithm: " << algorithm_name << std::endl;
    std::cout << "Selected Key: " << sort_key << (reverse_order ? " (Descending)" : " (Ascending)") << std::endl;
    if (limit_rows_opt) {
        std::cout << "Printing first " << limit_rows_opt.value() << " rows upon completion." << std::endl;
    }

    // 2. Load Data
    DatasetLoader loader(DEFAULT_CSV_PATH);
    std::cout << "\nLoading cities from " << DEFAULT_CSV_PATH << "..." << std::endl;
    std::vector<City> all_cities = loader.loadAndParseCities();
    // loadAndParseCities should print the number of cities parsed.
    if (all_cities.empty()) {
        std::cerr << "Warning: No cities were loaded. Check CSV file (" << DEFAULT_CSV_PATH
                << ") and parsing logic." << std::endl;
    }

    // 3. Create Sorter Instance
    std::unique_ptr<Sorter> sorter = SorterFactory::createSorter(algorithm_name);

    // 4. Create Comparator
    Sorter::Comparator comparator_fn = createComparator(sort_key, reverse_order);

    // For a single run, we sort a copy of all_cities.
    // For performance tests, you would loop here for different sizes (1k, 10k, complete)
    // and ensure 'data_to_sort' is a fresh copy of the desired subset for each run.
    std::vector<City> data_to_sort = all_cities; // Make a copy for sorting

    if (data_to_sort.empty()) {
        std::cout << "\nNo data to sort." << std::endl;
    } else {
        std::cout << "\nSorting " << data_to_sort.size() << " cities using " << sorter->getName()
                << " by " << sort_key << "..." << std::endl;

        // 5. Perform Sorting and Timing
        auto start_time = std::chrono::high_resolution_clock::now();
        sorter->sort(data_to_sort, comparator_fn);
        auto end_time = std::chrono::high_resolution_clock::now();

        auto duration_chrono = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        long long sort_duration_ms = duration_chrono.count();

        std::cout << "Sorting completed in " << sort_duration_ms << " ms." << std::endl;

        // 6. Correctness Guard
        std::cout << "Verifying sort correctness..." << std::endl;
        bool is_correctly_sorted = std::is_sorted(data_to_sort.begin(), data_to_sort.end(), comparator_fn);

        if (!is_correctly_sorted) {
            std::cerr << "CRITICAL ERROR: The data was NOT sorted correctly by " << sorter->getName() << "!" << std::endl;
            // To ensure the program exits with an error code for scripting if assert is disabled (NDEBUG)
            assert(is_correctly_sorted && "Assertion failed: Data is NOT sorted correctly!");

        } else {
            std::cout << "Sort verification successful." << std::endl;
        }
    }

    // 7. Print Results (conditionally)
    // Pass the sorted data 'data_to_sort', not 'all_cities'
    printCities(data_to_sort, limit_rows_opt);
}


// --- Performance Test Mode ---
void runPerformanceTests() {
    std::cout << "Starting Performance Test Mode..." << std::endl;
    std::cout << "Algorithm,Key,Size,Time(ms)" << std::endl; // CSV Header for output

    // Define algorithms, keys, and sizes to test
    const std::vector<std::string> algorithms_to_test = {"bubble", "insertion", "merge", "quick", "heap", "std"};
    const std::vector<std::string> keys_to_test = {"name", "population", "lat"}; // As per Req 6 "three keys"
    const std::vector<size_t> sizes_to_test = {1000, 10000}; // 1k, 10k
    // "complete" will be handled separately or as the largest size if data is smaller

    // 1. Load Full Dataset ONCE
    DatasetLoader loader(DEFAULT_CSV_PATH);
    std::vector<City> all_cities;
    try {
        all_cities = loader.loadAndParseCities();
        if (all_cities.empty()) {
            std::cerr << "Performance Test Error: No cities loaded. Aborting." << std::endl;
            return;
        }
        std::cout << "# Full dataset size: " << all_cities.size() << " cities." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Performance Test Error during data loading: " << e.what() << std::endl;
        return;
    }

    // Optional: Shuffle the full dataset once to make subsets more random
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(all_cities.begin(), all_cities.end(), g);
    std::cout << "# Full dataset shuffled for subsetting." << std::endl;


    for (const auto& algo_name : algorithms_to_test) {
        std::unique_ptr<Sorter> sorter;
        try {
            sorter = SorterFactory::createSorter(algo_name);
        } catch (const std::exception& e) {
            std::cerr << "Error creating sorter " << algo_name << ": " << e.what() << ". Skipping." << std::endl;
            continue;
        }

        for (const auto& key_name : keys_to_test) {
            Sorter::Comparator comparator_asc = createComparator(key_name, false); // Test ascending
            // Sorter::Comparator comparator_desc = createComparator(key_name, true); // Optionally test descending too

            // Test with defined sizes (1k, 10k)
            for (size_t current_size : sizes_to_test) {
                if (current_size > all_cities.size()) {
                    std::cout << "# Skipping size " << current_size << " for " << algo_name << "/" << key_name
                              << " as it exceeds total data size (" << all_cities.size() << ")." << std::endl;
                    continue;
                }

                std::vector<City> data_subset(all_cities.begin(), all_cities.begin() + current_size);

                auto start_time = std::chrono::high_resolution_clock::now();
                sorter->sort(data_subset, comparator_asc);
                auto end_time = std::chrono::high_resolution_clock::now();
                auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

                // Output in CSV format
                std::cout << algo_name << "," << key_name << "," << current_size << "," << duration_ms << std::endl;

                // Correctness check (optional here, but good for sanity during development)
                // assert(std::is_sorted(data_subset.begin(), data_subset.end(), comparator_asc));
            }

            // Test with "complete" dataset
            std::vector<City> data_complete = all_cities; // Fresh copy
            auto start_time_complete = std::chrono::high_resolution_clock::now();
            sorter->sort(data_complete, comparator_asc);
            auto end_time_complete = std::chrono::high_resolution_clock::now();
            auto duration_ms_complete = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_complete - start_time_complete).count();

            std::cout << algo_name << "," << key_name << "," << all_cities.size() << "," << duration_ms_complete << std::endl;
            // assert(std::is_sorted(data_complete.begin(), data_complete.end(), comparator_asc));
        }
    }
    std::cout << "Performance Test Mode Finished." << std::endl;
}
int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    try {
        // 1. Parse Command Line Arguments
        CliParser cli_parser(argc, argv);

        if (cli_parser.isPerformanceTestMode()) {
            runPerformanceTests(); // New function to handle all performance tests
        } else {
            run_single_sort(cli_parser);
        }


    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\nApplication finished successfully." << std::endl;
    return 0;
}
