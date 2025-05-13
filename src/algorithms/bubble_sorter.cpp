//
// Created by Miko on 5/13/2025.
//

#include "../../include/algorithms/bubble_sorter.hpp"
#include <vector>
#include <string>
#include <utility>

std::string BubbleSorter::getName() const {
    return "bubble";
}

void BubbleSorter::sort(std::vector<City>& cities, Comparator compare) {
    if (cities.size() < 2) {
        return; // Already sorted
    }

    size_t n = cities.size();
    bool swapped;
    for (size_t i = 0; i < n - 1; ++i) {
        swapped = false;
        for (size_t j = 0; j < n - 1 - i; ++j) {
            if (compare(cities[j + 1], cities[j])) {
                std::swap(cities[j], cities[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}