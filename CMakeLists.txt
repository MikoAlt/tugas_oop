cmake_minimum_required(VERSION 3.30)
project(tugas_oop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)


# include the CMake module for FetchContent
include(FetchContent)

# --- FetchContent for GoogleTest ---
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)



# --- Define a Library for Core Components ---
# This library will encapsulate cli_parser, csv_parser, dataset_loader, city.hpp, etc.
add_library(CoreUtils
        src/cli_parser.cpp
        src/csv_parser.cpp
        src/dataset_loader.cpp
        # city.hpp is header-only but its include path is managed here
)
# Public include directory for CoreUtils: headers directly in "include/"
target_include_directories(CoreUtils PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include> # For installation, if you were to install this lib
)
# So, anyone linking to CoreUtils automatically gets access to headers in "include/"
# using #include "city.hpp", #include "cli_parser.hpp", etc.

# --- Define a Library for Sorting Algorithms ---
# This library will encapsulate all algorithm implementations and their headers.
file(GLOB ALGORITHM_SRC_FILES "src/algorithms/*.cpp")
add_library(SortingAlgorithms ${ALGORITHM_SRC_FILES})

# The Sorter interface is a dependency for SortingAlgorithms
target_link_libraries(SortingAlgorithms PUBLIC CoreUtils) # Because sorter.hpp is in CoreUtils' public includes

# Public include directory for SortingAlgorithms: headers in "include/algorithms/"
# Consumers will need to use #include "algorithms/bubble_sorter.hpp"
target_include_directories(SortingAlgorithms PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include> # Provides access to "algorithms/" subdir
        $<INSTALL_INTERFACE:include>
)
# Note: This setup means that to include an algorithm header, you'd do:
# #include "algorithms/bubble_sorter.hpp"
# And algorithm headers (e.g., bubble_sorter.hpp) would include sorter.hpp via:
# #include "sorter.hpp" (because CoreUtils is linked and its include path is propagated)

# --- Define a Library for the Sorter Factory ---
add_library(SorterFactoryLib src/sorter_factory.cpp)
target_link_libraries(SorterFactoryLib PUBLIC SortingAlgorithms CoreUtils)


# --- Define the Main Executable ---
add_executable(citysort src/main.cpp)

# --- Link Libraries to the Executable ---
# main.cpp will need functions/classes from all these libraries.
target_link_libraries(citysort PRIVATE
        CoreUtils
        SorterFactoryLib
)

# --- Copy worldcities.csv as a POST_BUILD step for citysort target ---
set(CSV_SOURCE_FILE ${PROJECT_SOURCE_DIR}/worldcities.csv)
if(NOT EXISTS ${CSV_SOURCE_FILE})
    message(FATAL_ERROR "Source CSV file not found: ${CSV_SOURCE_FILE}")
endif()

add_custom_command(
        TARGET citysort # Associated with the citysort target
        POST_BUILD      # Execute this command *after* citysort has been built
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CSV_SOURCE_FILE}"
        "$<TARGET_FILE_DIR:citysort>/worldcities.csv" # Destination next to the executable
        COMMENT "Copying worldcities.csv to citysort output directory"
        VERBATIM
)

# The include directories are propagated via target_link_libraries from the PUBLIC/INTERFACE properties.

# --- Optional: Compiler Warnings ---
if(MSVC)
    target_compile_options(citysort PRIVATE /W4)
    target_compile_options(CoreUtils PRIVATE /W4)
    target_compile_options(SortingAlgorithms PRIVATE /W4)
    target_compile_options(SorterFactoryLib PRIVATE /W4)
else()
    target_compile_options(citysort PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(CoreUtils PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(SortingAlgorithms PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(SorterFactoryLib PRIVATE -Wall -Wextra -Wpedantic)
endif()




# --- Output some information ---
message(STATUS "CMake version: ${CMAKE_VERSION}")
message(STATUS "CMake generator: ${CMAKE_GENERATOR}")
message(STATUS "worldcities.csv will be copied from ${CSV_SOURCE_PATH} to ${CSV_DESTINATION_PATH}")
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Building executable: citysort")

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND NOT DEFINED ENV{CMAKE_DISABLE_TESTING})
    # More robust check if we are in the top-level project.
    # The CMAKE_DISABLE_TESTING environment variable can also be used to skip tests.
    option(BUILD_TESTING "Build unit tests" ON) # Make it an explicit option, defaults to ON
else()
    option(BUILD_TESTING "Build unit tests" OFF)
endif()


if(BUILD_TESTING)
    enable_testing() # Enables CTest support

    message(STATUS "BUILD_TESTING is ON. Setting up tests...")

    # --- Find Test Source Files ---
    file(GLOB_RECURSE TEST_SRC_FILES "tests/*.cpp" )

    if(NOT TEST_SRC_FILES)
        message(WARNING "No test source files found in tests/*.cpp. Skipping test executable creation.")
    else()
        # --- Create Test Executable ---
        add_executable(runCitySortTests ${TEST_SRC_FILES})

        # --- Link Test Executable ---
        target_link_libraries(runCitySortTests PRIVATE gtest_main) # From GoogleTest
        target_link_libraries(runCitySortTests PRIVATE
                CoreUtils
                SortingAlgorithms
                SorterFactoryLib
        )

        # --- Add Tests to CTest ---
        include(GoogleTest) # Must be after add_executable and target_link_libraries
        gtest_discover_tests(runCitySortTests)

        message(STATUS "Test executable 'runCitySortTests' will be built with sources: ${TEST_SRC_FILES}")

        # Apply compiler warnings to test executable as well
        if(MSVC)
            target_compile_options(runCitySortTests PRIVATE /W4)
        else()
            target_compile_options(runCitySortTests PRIVATE -Wall -Wextra -Wpedantic)
        endif()
    endif()
else()
    message(STATUS "BUILD_TESTING is OFF. Unit tests will not be built.")
endif()