//
// Created by Miko on 5/13/2025.
//

#ifndef HEAP_SORTER_HPP
#define HEAP_SORTER_HPP

#include <sorter.hpp>
#include <vector>
#include <string>

class HeapSorter : public Sorter {
public:
    void sort(std::vector<City>& cities, Comparator compare) override;
    [[nodiscard]] std::string getName() const override;

private:
    // To heapify a subtree rooted with node i which is an index in cities[].
    // n is size of heap. compare defines the heap property (max-heap if compare(a,b) means a<b).
    void heapify(std::vector<City>& cities, size_t n, size_t i, Comparator& compare);
};

#endif // HEAP_SORTER_HPP
