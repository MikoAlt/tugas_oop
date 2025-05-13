//
// Created by Miko on 5/13/2025.
//

#include <gtest/gtest.h>
#include <algorithms/bubble_sorter.hpp> // Sorter being tested
#include "sorter_test_utils.hpp"       // Common test utilities

// Test fixture for BubbleSorter
class BubbleSorterTest : public ::testing::Test {
protected:
    BubbleSorter sorter_instance;         // Instance of the sorter
    SorterTestData test_data_provider;    // Provides various test datasets
};

TEST_F(BubbleSorterTest, GetName) {
    EXPECT_EQ(sorter_instance.getName(), "bubble");
}

TEST_F(BubbleSorterTest, SortsEmptyVector) {
    std::vector<City> data = test_data_provider.cities_empty;
    auto comparator = TestComparators::byPopulation();
    sorter_instance.sort(data, comparator);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end(), comparator));
    EXPECT_TRUE(data.empty());
}

TEST_F(BubbleSorterTest, SortsSingleElementVector) {
    std::vector<City> data = test_data_provider.cities_one;
    auto comparator = TestComparators::byName();
    sorter_instance.sort(data, comparator);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end(), comparator));
    ASSERT_EQ(data.size(), 1);
    EXPECT_EQ(data[0].name, "LonelyCity");
}

TEST_F(BubbleSorterTest, SortsUnsortedSampleByNameAscending) {
    std::vector<City> data = test_data_provider.cities_sample_unsorted;
    auto comparator = TestComparators::byName(false);
    sorter_instance.sort(data, comparator);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end(), comparator));
    // Example: Smallest name should be first
    if (!data.empty()) EXPECT_EQ(data[0].name, "Cairo");
}

TEST_F(BubbleSorterTest, SortsUnsortedSampleByPopulationDescending) {
    std::vector<City> data = test_data_provider.cities_sample_unsorted;
    auto comparator = TestComparators::byPopulation(true); // Descending
    sorter_instance.sort(data, comparator);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end(), comparator));
    // Example: Largest population should be first
    if (!data.empty()) EXPECT_EQ(data[0].name, "Tokyo");
}

TEST_F(BubbleSorterTest, SortsAlreadySortedByName) {
    std::vector<City> data = test_data_provider.cities_already_sorted_by_name;
    auto comparator = TestComparators::byName(false);
    sorter_instance.sort(data, comparator); // Sort again
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end(), comparator));
    // Verify it didn't mess up the order (element-wise comparison)
    ASSERT_EQ(data.size(), test_data_provider.cities_already_sorted_by_name.size());
    for(size_t i = 0; i < data.size(); ++i) {
        EXPECT_EQ(data[i].name, test_data_provider.cities_already_sorted_by_name[i].name);
    }
}

TEST_F(BubbleSorterTest, SortsReverseSortedByName) {
    std::vector<City> data = test_data_provider.cities_reverse_sorted_by_name;
    auto comparator = TestComparators::byName(false); // Sort ascending
    sorter_instance.sort(data, comparator);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end(), comparator));
    if (!data.empty()) EXPECT_EQ(data[0].name, "Cairo"); // Smallest name
}

TEST_F(BubbleSorterTest, SortsDataWithDuplicatesByName_CheckStability) {
    // Bubble Sort is stable.
    // stability_test_data_name: CityA (X), CityB, CityA (Z)
    // Expected after sort by name: CityA (X), CityA (Z), CityB
    // The relative order of ("CityA", "CountryX") and ("CityA", "CountryZ") should be preserved.
    std::vector<City> data = test_data_provider.stability_test_data_name;
    auto original_cityA_X = data[0]; // Assuming this is CityA, CountryX
    auto original_cityA_Z = data[2]; // Assuming this is CityA, CountryZ

    auto comparator = TestComparators::byName(false);
    sorter_instance.sort(data, comparator);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end(), comparator));

    ASSERT_EQ(data.size(), 3);
    // Check that the two "CityA"s are first and their original relative order is maintained
    EXPECT_EQ(data[0].name, "CityA");
    EXPECT_EQ(data[0].country, "CountryX"); // original_cityA_X was first among CityA's

    EXPECT_EQ(data[1].name, "CityA");
    EXPECT_EQ(data[1].country, "CountryZ"); // original_cityA_Z was second among CityA's

    EXPECT_EQ(data[2].name, "CityB");
}

TEST_F(BubbleSorterTest, SortsDataWithDuplicatesByPopulation_CheckStability) {
    // Bubble Sort is stable.
    // stability_test_data_population: CityB (Pop 500), CityA (Pop 1000), CityC (Pop 500)
    // Expected after sort by pop: CityB (500), CityC (500), CityA (1000)
    // Relative order of CityB (500) and CityC (500) should be preserved.
    std::vector<City> data = test_data_provider.stability_test_data_population;

    auto comparator = TestComparators::byPopulation(false);
    sorter_instance.sort(data, comparator);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end(), comparator));

    ASSERT_EQ(data.size(), 3);
    // Check that the two cities with population 500 are first and their original relative order is maintained
    EXPECT_EQ(data[0].name, "CityB"); // CityB (pop 500) was before CityC (pop 500)
    EXPECT_EQ(data[0].population, 500L);

    EXPECT_EQ(data[1].name, "CityC");
    EXPECT_EQ(data[1].population, 500L);

    EXPECT_EQ(data[2].name, "CityA");
    EXPECT_EQ(data[2].population, 1000L);
}