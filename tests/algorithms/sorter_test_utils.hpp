//
// Created by Miko on 5/13/2025.
//

#ifndef SORTER_TEST_UTILS_HPP
#define SORTER_TEST_UTILS_HPP

#include <city.hpp>   // Assuming this is accessible via include paths from CMake
#include <sorter.hpp> // Assuming this is accessible
#include <vector>
#include <string>
#include <algorithm> // For std::sort, std::is_sorted
#include <functional>

namespace TestComparators {
    // Using inline for C++17+ to allow definitions in header, or make them static inline for older standards
    // or declare here and define in a separate .cpp file linked to tests.
    // For simplicity with header-only test utils, inline is fine.
    inline Sorter::Comparator byPopulation(bool reverse = false) {
        return [reverse](const City& a, const City& b) {
            return reverse ? (b.population < a.population) : (a.population < b.population);
        };
    }
    inline Sorter::Comparator byName(bool reverse = false) {
        return [reverse](const City& a, const City& b) {
            return reverse ? (b.name < a.name) : (a.name < b.name);
        };
    }
    inline Sorter::Comparator byLatitude(bool reverse = false) {
        return [reverse](const City& a, const City& b) {
            return reverse ? (b.lat < a.lat) : (a.lat < b.lat);
        };
    }
    inline Sorter::Comparator byLongitude(bool reverse = false) {
        return [reverse](const City& a, const City& b) {
            return reverse ? (b.lng < a.lng) : (a.lng < b.lng);
        };
    }
    inline Sorter::Comparator byCountry(bool reverse = false) {
        return [reverse](const City& a, const City& b) {
            return reverse ? (b.country < a.country) : (a.country < b.country);
        };
    }
} // namespace TestComparators

struct SorterTestData {
    std::vector<City> cities_empty;
    std::vector<City> cities_one {{"LonelyCity", "Solitude", 10.0, 20.0, 1}};
    std::vector<City> cities_sample_unsorted {
        {"Tokyo", "Japan", 35.6897, 139.6922, 37435191L},
        {"Delhi", "India", 28.6139, 77.2090, 29399141L},
        {"New York", "USA", 40.7128, -74.0060, 8398748L},
        {"Shanghai", "China", 31.2304, 121.4737, 26317104L},
        {"Cairo", "Egypt", 30.0444, 31.2357, 20484965L}
    };
    std::vector<City> cities_already_sorted_by_name;
    std::vector<City> cities_reverse_sorted_by_name;
    std::vector<City> cities_with_duplicates { // For stability checks
        {"CityA", "CountryX", 10.0, 10.0, 1000L}, // Original index 0
        {"CityB", "CountryY", 20.0, 20.0, 500L},  // Original index 1
        {"CityA", "CountryZ", 30.0, 30.0, 1500L}, // Original index 2, same name as [0]
        {"CityC", "CountryW", 40.0, 40.0, 500L}   // Original index 3, same pop as [1]
    };

    // More specific data for stability tests
    std::vector<City> stability_test_data_name { // CityA_X should remain before CityA_Z if stable
        {"CityA", "CountryX", 10.0, 10.0, 1000L},
        {"CityB", "CountryY", 20.0, 20.0, 500L},
        {"CityA", "CountryZ", 30.0, 30.0, 1500L}
    };
     std::vector<City> stability_test_data_population { // CityB_500 should remain before CityC_500 if stable
        {"CityB", "CountryY", 20.0, 20.0, 500L},
        {"CityA", "CountryX", 10.0, 10.0, 1000L},
        {"CityC", "CountryW", 40.0, 40.0, 500L}
    };


    SorterTestData() { // Constructor to initialize derived test data
        cities_already_sorted_by_name = cities_sample_unsorted;
        std::sort(cities_already_sorted_by_name.begin(), cities_already_sorted_by_name.end(), TestComparators::byName(false));

        cities_reverse_sorted_by_name = cities_sample_unsorted;
        std::sort(cities_reverse_sorted_by_name.begin(), cities_reverse_sorted_by_name.end(), TestComparators::byName(true));
    }
};

#endif // SORTER_TEST_UTILS_HPP