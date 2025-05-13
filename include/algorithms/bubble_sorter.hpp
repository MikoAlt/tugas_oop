//
// Created by Miko on 5/13/2025.
//

#ifndef BUBBLE_SORTER_HPP
#define BUBBLE_SORTER_HPP

#include <sorter.hpp> // Include the base class Sorter interface
#include <vector>
#include <string>

class BubbleSorter : public Sorter {
public:
    void sort(std::vector<City>& cities, Comparator compare) override;

    [[nodiscard]] std::string getName() const override;
};

#endif // BUBBLE_SORTER_HPP
