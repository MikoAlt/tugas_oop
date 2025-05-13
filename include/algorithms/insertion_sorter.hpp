//
// Created by Miko on 5/13/2025.
//

#ifndef INSERTION_SORTER_HPP
#define INSERTION_SORTER_HPP

#include <sorter.hpp>
#include <vector>
#include <string>

class InsertionSorter : public Sorter {
public:
    void sort(std::vector<City>& cities, Comparator compare) override;
    [[nodiscard]] std::string getName() const override;
};

#endif // INSERTION_SORTER_HPP
