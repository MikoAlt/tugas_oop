//
// Created by Miko on 5/13/2025.
//

#include "../../include/algorithms/insertion_sorter.hpp"
#include <vector>
#include <string>
#include <utility> // For std::move (optional optimization)

std::string InsertionSorter::getName() const {
    return "insertion";
}

void InsertionSorter::sort(std::vector<City>& cities, Comparator compare) {
    if (cities.size() < 2) {
        return;
    }

    for (size_t i = 1; i < cities.size(); ++i) {
        City key = std::move(cities[i]); // Use move for potential efficiency
        long long j = static_cast<long long>(i) - 1; // Use signed type for comparison with -1
        while (j >= 0 && compare(key, cities[j])) {
            cities[j + 1] = std::move(cities[j]); // Use move
            j = j - 1;
        }
        cities[j + 1] = std::move(key); // Use move
    }
}