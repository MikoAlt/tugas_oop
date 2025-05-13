//
// Created by Miko on 5/12/2025.
//

#ifndef CLI_PARSER_HPP
#define CLI_PARSER_HPP

#include <string>
#include <vector>
#include <optional>

/**
 * @class CliParser
 * @brief Command-line interface argument parser for algorithm selection and configuration.
 *
 * Parses command-line arguments to extract algorithm type, key, order, row limits, and performance test mode.
 * Provides accessors for parsed values and static utilities for valid options and usage printing.
 *
 * @note This class assumes arguments are passed in a specific format and validates them against predefined lists.
 *
 * @param argc Argument count from main().
 * @param argv Argument vector from main().
 *
 * @method getAlgorithm() Returns the selected algorithm as a string.
 * @method getKey() Returns the selected key as a string.
 * @method isReverseOrder() Returns true if reverse order is enabled.
 * @method getLimitRows() Returns an optional integer specifying row limit, if set.
 * @method printUsage() Prints usage information for the program.
 * @method isPerformanceTestMode() Returns true if performance test mode is enabled.
 * @method getValidAlgorithms() Returns a list of valid algorithm names.
 * @method getValidKeys() Returns a list of valid key names.
 *
 * @private
 * @var algorithm_ Stores the selected algorithm.
 * @var key_ Stores the selected key.
 * @var reverse_order_ Indicates if reverse order is enabled.
 * @var performance_test_mode_ Indicates if performance test mode is enabled.
 * @var limit_rows_ Stores the optional row limit.
 * @var valid_algorithms_ Static list of valid algorithms.
 * @var valid_keys_ Static list of valid keys.
 *
 * @private
 * @method parseArguments() Parses and validates command-line arguments.
 * @method isValidAlgorithm() Checks if a given algorithm is valid.
 * @method isValidKey() Checks if a given key is valid.
 */
class CliParser {
public:
    CliParser(int argc, char* argv[]);

    [[nodiscard]] const std::string& getAlgorithm() const;
    [[nodiscard]] const std::string& getKey() const;
    [[nodiscard]] bool isReverseOrder() const;
    [[nodiscard]] std::optional<int> getLimitRows() const;

    static void printUsage(const char* programName);
    [[nodiscard]] bool isPerformanceTestMode() const;
    [[nodiscard]] static const std::vector<std::string>& getValidAlgorithms();
    [[nodiscard]] static const std::vector<std::string>& getValidKeys();

private:
    std::string algorithm_;
    std::string key_;
    bool reverse_order_ = false;
    bool performance_test_mode_ = false;
    std::optional<int> limit_rows_;

    static const std::vector<std::string> valid_algorithms_;
    static const std::vector<std::string> valid_keys_;

    void parseArguments(int argc, char* argv[]);
    [[nodiscard]] static bool isValidAlgorithm(const std::string& algo) ;
    [[nodiscard]] static bool isValidKey(const std::string& key) ;

};

#endif // CLI_PARSER_HPP
