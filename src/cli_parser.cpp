//
// Created by Miko on 5/12/2025.
//

#include <cli_parser.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <optional>
#include <algorithm>

const std::vector<std::string> CliParser::valid_algorithms_ = {
    "bubble", "insertion", "merge", "quick", "heap", "std"
};

const std::vector<std::string> CliParser::valid_keys_ = {
    "name", "country", "population", "lat", "lng"
};

const std::vector<std::string>& CliParser::getValidAlgorithms() {
    return valid_algorithms_;
}

const std::vector<std::string>& CliParser::getValidKeys() {
    return valid_keys_;
}


CliParser::CliParser(int argc, char* argv[]) {
    this->limit_rows_ = std::nullopt;
    this->parseArguments(argc, argv);

    if (algorithm_.empty() && !performance_test_mode_) {
        CliParser::printUsage(argv[0]);
        throw std::runtime_error("Error: Missing required argument -a <algo>.");
    }
    if (key_.empty() && !performance_test_mode_) {
        CliParser::printUsage(argv[0]);
        throw std::runtime_error("Error: Missing required argument -k <key>.");
    }
}

void CliParser::parseArguments(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-a") {
            if (i + 1 < argc) {
                this->algorithm_ = argv[++i];
                if (!isValidAlgorithm(algorithm_)) {
                    throw std::invalid_argument("Error: Invalid algorithm specified: " + algorithm_);
                }
            } else {
                printUsage(argv[0]);
                throw std::runtime_error("Error: Argument -a requires a value <algo>.");
            }
        } else if (arg == "-k") {
            if (i + 1 < argc) {
                this->key_ = argv[++i];
                 if (!isValidKey(key_)) {
                    throw std::invalid_argument("Error: Invalid key specified: " + key_);
                }
            } else {
                printUsage(argv[0]);
                throw std::runtime_error("Error: Argument -k requires a value <key>.");
            }
        } else if (arg == "-r") {
            this->reverse_order_ = true;
        } else if (arg == "-n") {
            if (i + 1 < argc) {
                try {
                    int n_value = std::stoi(argv[++i]);
                    if (n_value <= 0) {
                         throw std::invalid_argument("Error: Value for -n must be a positive integer.");
                    }
                    this->limit_rows_ = n_value;
                } catch (const std::invalid_argument&) {
                    throw std::invalid_argument("Error: Invalid integer value provided for -n.");
                } catch (const std::out_of_range&) {
                    throw std::out_of_range("Error: Integer value for -n is out of range.");
                }
            } else {
                CliParser::printUsage(argv[0]);
                throw std::runtime_error("Error: Argument -n requires an integer value N.");
            }
        } else if (arg == "--performance-test" || arg == "-P") { // Choose one or both
            this->performance_test_mode_ = true;
        } else {
            printUsage(argv[0]);
            throw std::runtime_error("Error: Unrecognized argument: " + arg);
        }
    }
}

bool CliParser::isValidAlgorithm(const std::string& algo) {
    return std::find(CliParser::valid_algorithms_.begin(), CliParser::valid_algorithms_.end(), algo) != CliParser::valid_algorithms_.end();
}

bool CliParser::isValidKey(const std::string& key) {
     return std::find(CliParser::valid_keys_.begin(), CliParser::valid_keys_.end(), key) != CliParser::valid_keys_.end();
}

const std::string& CliParser::getAlgorithm() const {
    return this->algorithm_;
}

const std::string& CliParser::getKey() const {
    return this->key_;
}

bool CliParser::isReverseOrder() const {
    return this->reverse_order_;
}

std::optional<int> CliParser::getLimitRows() const {
    return this->limit_rows_;
}

bool CliParser::isPerformanceTestMode() const {
    return this->performance_test_mode_;
}

void CliParser::printUsage(const char* programName) {
    std::cerr << "Usage: " << (programName ? programName : "citysort")
              << " -a <algo> -k <key> [-r] [-n N]\n"
              << "\nOptions:\n"
              << "  -a <algo>         : Sorting algorithm. Required.\n"
              << "                      <algo>: bubble|insertion|merge|quick|heap|std\n"
              << "  -k <key>          : Sorting key (column). Required.\n"
              << "                      <key>: name|country|population|lat|lng\n"
              << "  -r                : Reverse sort order (descending). Optional.\n"
              << "  -n N              : Print only the first N rows. Optional. N must be > 0.\n"
              << "  --performace-test  -P : Run performance logging on all algorithm (this will ignore every other flags).\n"
              << std::endl;
}

