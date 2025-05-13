//
// Created by Miko on 5/13/2025.
//

#ifndef STD_SORTER_HPP
#define STD_SORTER_HPP

#include <sorter.hpp>
#include <vector>
#include <string>

class StdSorter : public Sorter {
public:
    void sort(std::vector<City>& cities, Comparator compare) override;
    [[nodiscard]] std::string getName() const override;
};

#endif // STD_SORTER_HPP
