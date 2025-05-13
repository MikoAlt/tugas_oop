//
// Created by Miko on 5/13/2025.
//

#ifndef SORTER_FACTORY_HPP
#define SORTER_FACTORY_HPP

#include <string>
#include <memory>   // For std::unique_ptr
#include <stdexcept> // For std::invalid_argument

// Forward declaration of the Sorter interface
// Avoids including the full sorter.hpp here, can speed up compilation slightly
// if sorter.hpp is complex, but requires including sorter.hpp in the .cpp file.
class Sorter;

// Factory class to create Sorter objects based on algorithm name.
class SorterFactory {
public:
    // Creates and returns a unique pointer to a Sorter object.
    // Throws std::invalid_argument if the algorithm name is not recognized.
    // Making it static allows calling it without creating a SorterFactory instance.
    static std::unique_ptr<Sorter> createSorter(const std::string& algorithm_name);
};

#endif // SORTER_FACTORY_HPP
