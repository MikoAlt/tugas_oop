//
// Created by Miko on 5/13/2025.
//

#include "gtest/gtest.h"
#include "algorithms/merge_sorter.hpp" // Sorter being tested
#include "sorter_test_utils.hpp"      // Common test utilities

// Test fixture for MergeSorter
class MergeSorterTest : public ::testing::Test {
protected:
    MergeSorter sorter_instance;
    SorterTestData test_data_provider;
};

TEST_F(MergeSorterTest, GetName) {
    EXPECT_EQ(sorter_instance.getName(), "merge");
}

TEST_F(MergeSorterTest, SortsEmptyVector) {
    std::vector<City> data = test_data_provider.cities_empty;
    auto comparator = TestComparators::byPopulation();
    sorter_instance.sort(data, comparator);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end(), comparator));
}

TEST_F(MergeSorterTest, SortsSingleElementVector) {
    std::vector<City> data = test_data_provider.cities_one;
    auto comparator = TestComparators::byName();
    sorter_instance.sort(data, comparator);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end(), comparator));
}

TEST_F(MergeSorterTest, SortsUnsortedSampleByNameAscending) {
    std::vector<City> data = test_data_provider.cities_sample_unsorted;
    auto comparator = TestComparators::byName(false);
    sorter_instance.sort(data, comparator);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end(), comparator));
    if (!data.empty()) EXPECT_EQ(data[0].name, "Cairo");
}

TEST_F(MergeSorterTest, SortsUnsortedSampleByPopulationDescending) {
    std::vector<City> data = test_data_provider.cities_sample_unsorted;
    auto comparator = TestComparators::byPopulation(true);
    sorter_instance.sort(data, comparator);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end(), comparator));
    if (!data.empty()) EXPECT_EQ(data[0].name, "Tokyo");
}

TEST_F(MergeSorterTest, SortsAlreadySortedByName) {
    std::vector<City> data = test_data_provider.cities_already_sorted_by_name;
    auto comparator = TestComparators::byName(false);
    sorter_instance.sort(data, comparator);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end(), comparator));
    ASSERT_EQ(data.size(), test_data_provider.cities_already_sorted_by_name.size());
    for(size_t i = 0; i < data.size(); ++i) {
        EXPECT_EQ(data[i].name, test_data_provider.cities_already_sorted_by_name[i].name);
    }
}

TEST_F(MergeSorterTest, SortsReverseSortedByName) {
    std::vector<City> data = test_data_provider.cities_reverse_sorted_by_name;
    auto comparator = TestComparators::byName(false);
    sorter_instance.sort(data, comparator);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end(), comparator));
    if (!data.empty()) EXPECT_EQ(data[0].name, "Cairo");
}

TEST_F(MergeSorterTest, SortsDataWithDuplicatesByName_CheckStability) {

    std::vector<City> data = test_data_provider.stability_test_data_name;

    auto comparator = TestComparators::byName(false);
    sorter_instance.sort(data, comparator);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end(), comparator));

    ASSERT_EQ(data.size(), 3);
    EXPECT_EQ(data[0].name, "CityA");
    EXPECT_EQ(data[0].country, "CountryX");

    EXPECT_EQ(data[1].name, "CityA");
    EXPECT_EQ(data[1].country, "CountryZ");

    EXPECT_EQ(data[2].name, "CityB");
}

TEST_F(MergeSorterTest, SortsDataWithDuplicatesByPopulation_CheckStability) {
    // Merge Sort is typically stable.
    // stability_test_data_population: CityB (Pop 500), CityA (Pop 1000), CityC (Pop 500)
    // Expected after sort by pop: CityB (500), CityC (500), CityA (1000)
    std::vector<City> data = test_data_provider.stability_test_data_population;

    auto comparator = TestComparators::byPopulation(false);
    sorter_instance.sort(data, comparator);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end(), comparator));

    ASSERT_EQ(data.size(), 3);
    EXPECT_EQ(data[0].name, "CityB");
    EXPECT_EQ(data[0].population, 500L);

    EXPECT_EQ(data[1].name, "CityC");
    EXPECT_EQ(data[1].population, 500L);

    EXPECT_EQ(data[2].name, "CityA");
    EXPECT_EQ(data[2].population, 1000L);
}