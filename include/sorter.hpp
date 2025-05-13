#ifndef SORTER_HPP
#define SORTER_HPP

#include <vector>
#include <functional> // For std::function
#include <string>
#include "city.hpp"   // Include the City struct definition

/**
 * @brief Abstract base class for sorting collections of City objects.
 *
 * The Sorter class defines an interface for sorting a vector of City objects
 * using a user-provided comparison function. Derived classes must implement
 * the sort algorithm and provide a name for the sorter.
 */
class Sorter {
public:
    /**
     * @brief Type alias for a comparator function used to compare two City objects.
     *
     * The comparator should return true if the first City should come before the second.
     */
    using Comparator = std::function<bool(const City&, const City&)>;

    /**
     * @brief Virtual destructor for proper cleanup of derived classes.
     */
    virtual ~Sorter() = default;

    /**
     * @brief Sorts a vector of City objects in-place using the provided comparator.
     *
     * @param cities The vector of City objects to be sorted.
     * @param compare The comparator function to determine the order of elements.
     */
    virtual void sort(std::vector<City>& cities, Comparator compare) = 0;

    /**
     * @brief Returns the name of the sorting algorithm.
     *
     * @return A string representing the name of the sorter.
     */
    [[nodiscard]] virtual std::string getName() const = 0;
};

#endif // SORTER_HPP