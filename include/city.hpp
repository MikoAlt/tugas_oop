//
// Created by Miko on 5/13/2025.
//

#ifndef CITY_HPP
#define CITY_HPP

#include <string>
#include <iostream> // Optional: for easy printing/debugging

struct City {
    std::string name;
    std::string country;
    double lat{};
    double lng{};
    long population{};

    // Overload ostream operator for printing of City objects
    friend std::ostream& operator<<(std::ostream& os, const City& city) {
        os << "City{name: \"" << city.name
           << "\", country: \"" << city.country
           << "\", lat: " << city.lat
           << ", lng: " << city.lng
           << ", population: " << city.population << "}";
        return os;
    }
};

#endif // CITY_HPP
