//
// Created by Miko on 5/13/2025.
//

#ifndef MERGE_SORTER_HPP
#define MERGE_SORTER_HPP

#include <sorter.hpp>
#include <vector>
#include <string>

class MergeSorter : public Sorter {
public:
    void sort(std::vector<City>& cities, Comparator compare) override;
    [[nodiscard]] std::string getName() const override;

private:
    // Helper recursive function
    void mergeSortRecursive(std::vector<City>& cities, std::vector<City>& temp, size_t left, size_t right, Comparator& compare);

    // Helper merge function
    static void merge(std::vector<City>& cities, std::vector<City>& temp, size_t left, size_t mid, size_t right, Comparator& compare);
};

#endif // MERGE_SORTER_HPP
