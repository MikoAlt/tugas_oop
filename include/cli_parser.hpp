//
// Created by Miko on 5/12/2025.
//

#ifndef CLI_PARSER_HPP
#define CLI_PARSER_HPP

#include <string>
#include <vector>
#include <optional>

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
