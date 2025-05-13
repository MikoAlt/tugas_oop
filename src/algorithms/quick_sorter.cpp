//
// Created by Miko on 5/13/2025.
//

#include "../../include/algorithms/quick_sorter.hpp"
#include <vector>
#include <string>
#include <utility> // For std::swap

std::string QuickSorter::getName() const {
    return "quick";
}

void QuickSorter::sort(std::vector<City>& cities, Comparator compare) {
    if (cities.size() < 2) {
        return;
    }
    // Need to cast size() - 1 to long long for the recursive helper
    quickSortRecursive(cities, 0, static_cast<long long>(cities.size()) - 1, compare);
}

// Lomuto partition scheme
long long QuickSorter::partition(std::vector<City>& cities, long long low, long long high, Comparator& compare) {
    City& pivot = cities[high]; // Choose the last element as pivot
    long long i = (low - 1); // Index of smaller element

    for (long long j = low; j <= high - 1; j++) {
        // If current element should come before pivot according to compare
        // compare(cities[j], pivot) means cities[j] < pivot
        if (compare(cities[j], pivot)) {
            i++; // increment index of smaller element
            std::swap(cities[i], cities[j]);
        }
    }
    std::swap(cities[i + 1], cities[high]); // Place pivot in correct position
    return (i + 1); // Return partition index
}

void QuickSorter::quickSortRecursive(std::vector<City>& cities, long long low, long long high, Comparator& compare) {
    if (low < high) {
        // pi is partitioning index, cities[pi] is now at right place
        long long pi = partition(cities, low, high, compare);

        // Separately sort elements before partition and after partition
        quickSortRecursive(cities, low, pi - 1, compare);
        quickSortRecursive(cities, pi + 1, high, compare);
    }
}