//
// Created by Miko on 5/13/2025.
//

#ifndef QUICK_SORTER_HPP
#define QUICK_SORTER_HPP

#include <sorter.hpp>
#include <vector>
#include <string>

class QuickSorter : public Sorter {
public:
    void sort(std::vector<City>& cities, Comparator compare) override;
    [[nodiscard]] std::string getName() const override;

private:
    // Helper recursive function
    void quickSortRecursive(std::vector<City>& cities, long long low, long long high, Comparator& compare);

    // Helper partition function (using Lomuto partition scheme as an example)
    static long long partition(std::vector<City>& cities, long long low, long long high, Comparator& compare);
};

#endif // QUICK_SORTER_HPP
