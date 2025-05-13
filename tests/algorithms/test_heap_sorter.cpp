//
// Created by Miko on 5/13/2025.
//

#include "gtest/gtest.h"
#include "algorithms/heap_sorter.hpp" // Sorter being tested
#include "sorter_test_utils.hpp"      // Common test utilities

// Test fixture for HeapSorter
class HeapSorterTest : public ::testing::Test {
protected:
    HeapSorter sorter_instance;
    SorterTestData test_data_provider;
};

TEST_F(HeapSorterTest, GetName) {
    EXPECT_EQ(sorter_instance.getName(), "heap");
}

TEST_F(HeapSorterTest, SortsEmptyVector) {
    std::vector<City> data = test_data_provider.cities_empty;
    auto comparator = TestComparators::byPopulation();
    sorter_instance.sort(data, comparator);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end(), comparator));
}

TEST_F(HeapSorterTest, SortsSingleElementVector) {
    std::vector<City> data = test_data_provider.cities_one;
    auto comparator = TestComparators::byName();
    sorter_instance.sort(data, comparator);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end(), comparator));
}

TEST_F(HeapSorterTest, SortsUnsortedSampleByNameAscending) {
    std::vector<City> data = test_data_provider.cities_sample_unsorted;
    auto comparator = TestComparators::byName(false);
    sorter_instance.sort(data, comparator);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end(), comparator));
    if (!data.empty()) EXPECT_EQ(data[0].name, "Cairo");
}

TEST_F(HeapSorterTest, SortsUnsortedSampleByPopulationDescending) {
    std::vector<City> data = test_data_provider.cities_sample_unsorted;
    auto comparator = TestComparators::byPopulation(true);
    sorter_instance.sort(data, comparator);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end(), comparator));
    if (!data.empty()) EXPECT_EQ(data[0].name, "Tokyo");
}

TEST_F(HeapSorterTest, SortsAlreadySortedByName) {
    std::vector<City> data = test_data_provider.cities_already_sorted_by_name;
    auto comparator = TestComparators::byName(false);
    sorter_instance.sort(data, comparator);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end(), comparator));
    ASSERT_EQ(data.size(), test_data_provider.cities_already_sorted_by_name.size());
    for(size_t i = 0; i < data.size(); ++i) {
        EXPECT_EQ(data[i].name, test_data_provider.cities_already_sorted_by_name[i].name);
    }
}

TEST_F(HeapSorterTest, SortsReverseSortedByName) {
    std::vector<City> data = test_data_provider.cities_reverse_sorted_by_name;
    auto comparator = TestComparators::byName(false);
    sorter_instance.sort(data, comparator);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end(), comparator));
    if (!data.empty()) EXPECT_EQ(data[0].name, "Cairo");
}

