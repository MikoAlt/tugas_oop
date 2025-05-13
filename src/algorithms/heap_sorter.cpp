//
// Created by Miko on 5/13/2025.
//

#include "../../include/algorithms/heap_sorter.hpp"
#include <vector>
#include <string>
#include <utility> // For std::swap

std::string HeapSorter::getName() const {
    return "heap";
}

// To heapify a subtree rooted with node i.
// Assumes compare(a, b) means a < b for standard max-heap behavior.
void HeapSorter::heapify(std::vector<City>& cities, size_t n, size_t i, Comparator& compare) {
    size_t largest = i; // Initialize largest as root
    size_t left = 2 * i + 1; // left child
    size_t right = 2 * i + 2; // right child

    // If left child is larger than root (using inverted compare for max-heap)
    // compare(cities[largest], cities[left]) means largest < left
    if (left < n && compare(cities[largest], cities[left])) {
        largest = left;
    }

    // If right child is larger than largest so far
    // compare(cities[largest], cities[right]) means largest < right
    if (right < n && compare(cities[largest], cities[right])) {
        largest = right;
    }

    // If largest is not root
    if (largest != i) {
        std::swap(cities[i], cities[largest]);

        // Recursively heapify the affected sub-tree
        heapify(cities, n, largest, compare);
    }
}

void HeapSorter::sort(std::vector<City>& cities, Comparator compare) {
    size_t n = cities.size();
    if (n < 2) {
        return;
    }

    // Build heap (rearrange array) - starting from the last non-leaf node
    for (long long i = static_cast<long long>(n / 2) - 1; i >= 0; --i) {
        heapify(cities, n, static_cast<size_t>(i), compare);
    }

    // One by one extract an element from heap
    for (long long i = static_cast<long long>(n) - 1; i > 0; --i) {
        // Move current root to end
        std::swap(cities[0], cities[static_cast<size_t>(i)]);

        // call max heapify on the reduced heap
        heapify(cities, static_cast<size_t>(i), 0, compare);
    }
}