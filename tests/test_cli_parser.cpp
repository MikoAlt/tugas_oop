// tests/test_cli_parser.cpp

#include "gtest/gtest.h"
#include "cli_parser.hpp" // Assuming CMake makes "include" path available
#include <stdexcept>
#include <vector>
#include <string>
#include <optional>

// Test fixture for CliParser
class CliParserTest : public ::testing::Test {
protected:
    // Helper to create argv from a vector of strings
    std::vector<char*> create_argv(const std::vector<std::string>& args_str) {
        argv_storage_ = args_str;
        c_strs_.clear();
        for (std::string& s_mut : argv_storage_) {
            c_strs_.push_back(s_mut.data());
        }
        return c_strs_;
    }

private:
    std::vector<std::string> argv_storage_;
    std::vector<char*> c_strs_;
};

// --- Tests for Normal Mode (No Performance Flag) ---

TEST_F(CliParserTest, NormalMode_MissingRequiredArguments) {
    auto argv_vec = create_argv({"./citysort"}); // No -P, so -a and -k are required
    EXPECT_THROW(CliParser parser(static_cast<int>(argv_vec.size()), argv_vec.data()), std::runtime_error);

    argv_vec = create_argv({"./citysort", "-a"}); // No -P
    EXPECT_THROW(CliParser parser(static_cast<int>(argv_vec.size()), argv_vec.data()), std::runtime_error);

    argv_vec = create_argv({"./citysort", "-a", "merge"}); // No -P, Missing -k
    EXPECT_THROW(CliParser parser(static_cast<int>(argv_vec.size()), argv_vec.data()), std::runtime_error);

    argv_vec = create_argv({"./citysort", "-k", "name"}); // No -P, Missing -a
    EXPECT_THROW(CliParser parser(static_cast<int>(argv_vec.size()), argv_vec.data()), std::runtime_error);
}

TEST_F(CliParserTest, NormalMode_ValidArgumentsFull) {
    auto argv_vec = create_argv({"./citysort", "-a", "merge", "-k", "population", "-r", "-n", "100"});
    ASSERT_NO_THROW({
        CliParser parser(static_cast<int>(argv_vec.size()), argv_vec.data());
        EXPECT_EQ(parser.getAlgorithm(), "merge");
        EXPECT_EQ(parser.getKey(), "population");
        EXPECT_TRUE(parser.isReverseOrder());
        ASSERT_TRUE(parser.getLimitRows().has_value());
        EXPECT_EQ(parser.getLimitRows().value(), 100);
        EXPECT_FALSE(parser.isPerformanceTestMode());
    });
}

TEST_F(CliParserTest, NormalMode_ValidArgumentsMinimal) {
    auto argv_vec = create_argv({"./citysort", "-a", "std", "-k", "name"});
     ASSERT_NO_THROW({
        CliParser parser(static_cast<int>(argv_vec.size()), argv_vec.data());
        EXPECT_EQ(parser.getAlgorithm(), "std");
        EXPECT_EQ(parser.getKey(), "name");
        EXPECT_FALSE(parser.isReverseOrder());
        EXPECT_FALSE(parser.getLimitRows().has_value());
        EXPECT_FALSE(parser.isPerformanceTestMode());
    });
}

TEST_F(CliParserTest, NormalMode_InvalidAlgorithm) {
    auto argv_vec = create_argv({"./citysort", "-a", "unknown_algo", "-k", "name"});
    EXPECT_THROW(CliParser parser(static_cast<int>(argv_vec.size()), argv_vec.data()), std::invalid_argument);
}

TEST_F(CliParserTest, NormalMode_InvalidKey) {
    auto argv_vec = create_argv({"./citysort", "-a", "std", "-k", "unknown_key"});
    EXPECT_THROW(CliParser parser(static_cast<int>(argv_vec.size()), argv_vec.data()), std::invalid_argument);
}

TEST_F(CliParserTest, NormalMode_InvalidNValueNotANumber) {
    auto argv_vec = create_argv({"./citysort", "-a", "std", "-k", "name", "-n", "not_a_number"});
    EXPECT_THROW(CliParser parser(static_cast<int>(argv_vec.size()), argv_vec.data()), std::invalid_argument);
}

TEST_F(CliParserTest, NormalMode_InvalidNValueZero) {
    auto argv_vec = create_argv({"./citysort", "-a", "std", "-k", "name", "-n", "0"});
    EXPECT_THROW(CliParser parser(static_cast<int>(argv_vec.size()), argv_vec.data()), std::invalid_argument);
}

TEST_F(CliParserTest, NormalMode_InvalidNValueNegative) {
    auto argv_vec = create_argv({"./citysort", "-a", "std", "-k", "name", "-n", "-5"});
    EXPECT_THROW(CliParser parser(static_cast<int>(argv_vec.size()), argv_vec.data()), std::invalid_argument);
}

TEST_F(CliParserTest, NormalMode_UnrecognizedArgument) {
    auto argv_vec = create_argv({"./citysort", "-a", "std", "-k", "name", "--unknown-flag"});
    EXPECT_THROW(CliParser parser(static_cast<int>(argv_vec.size()), argv_vec.data()), std::runtime_error);
}


// --- Tests for Performance Flag ---

TEST_F(CliParserTest, PerformanceFlag_AloneIsValid_ShortOption) {
    // Test that -P ALONE is now a valid construction for CliParser
    auto argv_vec = create_argv({"./citysort", "-P"});
    ASSERT_NO_THROW({
        CliParser parser(static_cast<int>(argv_vec.size()), argv_vec.data());
        EXPECT_TRUE(parser.isPerformanceTestMode());
        EXPECT_TRUE(parser.getAlgorithm().empty()); // Algorithm is not required/set by -P
        EXPECT_TRUE(parser.getKey().empty());       // Key is not required/set by -P
        EXPECT_FALSE(parser.isReverseOrder());      // Defaults
        EXPECT_FALSE(parser.getLimitRows().has_value()); // Defaults
    });
}

TEST_F(CliParserTest, PerformanceFlag_AloneIsValid_LongOption) {
    auto argv_vec = create_argv({"./citysort", "--performance-test"});
    ASSERT_NO_THROW({
        CliParser parser(static_cast<int>(argv_vec.size()), argv_vec.data());
        EXPECT_TRUE(parser.isPerformanceTestMode());
        EXPECT_TRUE(parser.getAlgorithm().empty());
        EXPECT_TRUE(parser.getKey().empty());
    });
}

TEST_F(CliParserTest, PerformanceFlag_WithOtherArgs_ParsesAll) {
    // If -P is present, other args are still parsed by CliParser,
    // even if main logic for performance tests might ignore some of them.
    auto argv_vec = create_argv({"./citysort", "-P", "-a", "merge", "-k", "lat", "-n", "50", "-r"});
    ASSERT_NO_THROW({
        CliParser parser(static_cast<int>(argv_vec.size()), argv_vec.data());
        EXPECT_TRUE(parser.isPerformanceTestMode());
        EXPECT_EQ(parser.getAlgorithm(), "merge");  // Parsed
        EXPECT_EQ(parser.getKey(), "lat");          // Parsed
        ASSERT_TRUE(parser.getLimitRows().has_value());
        EXPECT_EQ(parser.getLimitRows().value(), 50); // Parsed
        EXPECT_TRUE(parser.isReverseOrder());         // Parsed
    });
}

TEST_F(CliParserTest, PerformanceFlag_WithMissingAlgo_StillValidForParser) {
    // -P is present, -a is missing, -k is present.
    // Parser should construct successfully because -P makes -a optional *for the parser*.
    auto argv_vec = create_argv({"./citysort", "-P", "-k", "name"});
    ASSERT_NO_THROW({
        CliParser parser(static_cast<int>(argv_vec.size()), argv_vec.data());
        EXPECT_TRUE(parser.isPerformanceTestMode());
        EXPECT_TRUE(parser.getAlgorithm().empty()); // Algo was not provided
        EXPECT_EQ(parser.getKey(), "name");         // Key was provided and parsed
    });
}

TEST_F(CliParserTest, PerformanceFlag_WithMissingKey_StillValidForParser) {
    // -P is present, -k is missing, -a is present.
    // Parser should construct successfully.
    auto argv_vec = create_argv({"./citysort", "-P", "-a", "std"});
    ASSERT_NO_THROW({
        CliParser parser(static_cast<int>(argv_vec.size()), argv_vec.data());
        EXPECT_TRUE(parser.isPerformanceTestMode());
        EXPECT_EQ(parser.getAlgorithm(), "std");    // Algo was provided
        EXPECT_TRUE(parser.getKey().empty());       // Key was not provided
    });
}