#ifndef SORTER_HPP
#define SORTER_HPP

#include <vector>
#include <functional> // For std::function
#include <string>
#include "city.hpp"   // Include the City struct definition

class Sorter {
public:
    using Comparator = std::function<bool(const City&, const City&)>;

    virtual ~Sorter() = default;

    // VIRTUAL, non-template sort using std::function for type erasure
    virtual void sort(std::vector<City>& cities, Comparator compare) = 0;

    [[nodiscard]] virtual std::string getName() const = 0;
};

#endif // SORTER_HPP