//
// Created by Miko on 5/13/2025.
//

#include <sorter_factory.hpp>

// Include the Sorter interface (remains in the main include directory)
#include <sorter.hpp>

// --- Include concrete Sorter implementations from the 'algorithms' subdirectory ---
#include <algorithms/bubble_sorter.hpp>
#include <algorithms/insertion_sorter.hpp>
#include <algorithms/merge_sorter.hpp>
#include <algorithms/quick_sorter.hpp>
#include <algorithms/heap_sorter.hpp>
#include <algorithms/std_sorter.hpp>

#include <unordered_map>
#include <functional>
#include <stdexcept>    

// --- IMPORTANT ---
// You MUST uncomment and include the actual header files for your
// concrete sorter implementations above, using the new paths.

// Define a type alias for the function that creates a Sorter unique_ptr
using SorterCreator = std::function<std::unique_ptr<Sorter>()>;

// Use a static map initialized once to store the mapping from name to creator function.
static const std::unordered_map<std::string, SorterCreator> sorter_registry = {
    {"bubble", []() -> std::unique_ptr<Sorter> {
        return std::make_unique<BubbleSorter>();
//        throw std::runtime_error("SorterFactory: BubbleSorter not yet implemented.");
    }},
    {"insertion", []() -> std::unique_ptr<Sorter> {
        return std::make_unique<InsertionSorter>();
//        throw std::runtime_error("SorterFactory: InsertionSorter not yet implemented.");
    }},
    {"merge", []() -> std::unique_ptr<Sorter> {
        return std::make_unique<MergeSorter>();
//        throw std::runtime_error("SorterFactory: MergeSorter not yet implemented.");
    }},
    {"quick", []() -> std::unique_ptr<Sorter> {
        return std::make_unique<QuickSorter>();
//        throw std::runtime_error("SorterFactory: QuickSorter not yet implemented.");
    }},
    {"heap", []() -> std::unique_ptr<Sorter> {
        return std::make_unique<HeapSorter>();
//        throw std::runtime_error("SorterFactory: HeapSorter not yet implemented.");
    }},
    {"std", []() -> std::unique_ptr<Sorter> {
        return std::make_unique<StdSorter>();
//        throw std::runtime_error("SorterFactory: StdSorter not yet implemented.");
    }}
};


std::unique_ptr<Sorter> SorterFactory::createSorter(const std::string& algorithm_name) {
    // Find the algorithm name in the registry map
    auto it = sorter_registry.find(algorithm_name);

    if (it != sorter_registry.end()) {
        // If found, call the associated creator function (stored as the map value)
        return it->second(); // it->second holds the SorterCreator lambda
    } else {
        // Algorithm name not found in the map
        throw std::invalid_argument("SorterFactory Error: Unknown sorting algorithm specified: " + algorithm_name);
    }
}