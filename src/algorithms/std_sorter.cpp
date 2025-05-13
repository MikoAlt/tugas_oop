//
// Created by Miko on 5/13/2025.
//

#include "../../include/algorithms/std_sorter.hpp"
#include <vector>
#include <string>
#include <algorithm> // For std::sort

std::string StdSorter::getName() const {
    return "std";
}

void StdSorter::sort(std::vector<City>& cities, Comparator compare) {
    std::sort(cities.begin(), cities.end(), compare);
}