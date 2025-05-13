//
// Created by Miko on 5/13/2025.
//

#include "../../include/algorithms/merge_sorter.hpp"
#include <vector>
#include <string>
#include <utility> // For std::move

std::string MergeSorter::getName() const {
    return "merge";
}

void MergeSorter::sort(std::vector<City>& cities, Comparator compare) {
    if (cities.size() < 2) {
        return;
    }
    std::vector<City> temp(cities.size()); // Allocate temporary space once
    this->mergeSortRecursive(cities, temp, 0, cities.size() - 1, compare);
}

void MergeSorter::mergeSortRecursive(std::vector<City>& cities, std::vector<City>& temp, size_t left, size_t right, Comparator& compare) {
    if (left >= right) {
        return; // Base case: 0 or 1 element
    }

    size_t mid = left + (right - left) / 2; // Avoid potential overflow
    this->mergeSortRecursive(cities, temp, left, mid, compare);
    this->mergeSortRecursive(cities, temp, mid + 1, right, compare);
    MergeSorter::merge(cities, temp, left, mid, right, compare);
}

void MergeSorter::merge(std::vector<City>& cities, std::vector<City>& temp, size_t left, size_t mid, size_t right, Comparator& compare) {
    size_t i = left;     // Pointer for the first part (left to mid) of original array
    size_t j = mid + 1;  // Pointer for the second part (mid+1 to right) of original array
    size_t k = left;     // Pointer for the temp array

    // While there are elements in both subarrays
    while (i <= mid && j <= right) {
        // To maintain stability:
        // If element from left subarray is less than OR EQUAL to element from right subarray,
        // pick from the left.
        // 'compare(a, b)' means 'a < b'.
        // So, 'cities[i] <= cities[j]' is equivalent to '!compare(cities[j], cities[i])'
        // (It's NOT the case that cities[j] is strictly less than cities[i]).
        if (!compare(cities[j], cities[i])) { // If cities[i] <= cities[j]
            temp[k++] = std::move(cities[i++]);
        } else { // cities[j] < cities[i]
            temp[k++] = std::move(cities[j++]);
        }
    }

    // Copy any remaining elements from the left subarray
    while (i <= mid) {
        temp[k++] = std::move(cities[i++]);
    }

    // Copy any remaining elements from the right subarray
    while (j <= right) {
        temp[k++] = std::move(cities[j++]);
    }

    // Copy the sorted subarray from temp back to cities
    for (size_t p = left; p <= right; ++p) {
        cities[p] = std::move(temp[p]);
    }
}