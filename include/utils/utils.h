#ifndef UTILS_H
#define UTILS_H
#include "basic_timer.h"
#include "parse_utils.h"
#include <algorithm>

namespace utils
{
    template <typename Map>
    bool mapContains(const Map &mp, const typename Map::key_type key)
    {
        return mp.find(key) != mp.end();
    }

    bool allAlpha(const std::string &str)
    {
        return std::all_of(str.begin(), str.end(), [](const char e)
                           { return std::isalpha(e); });
    }

    bool allDigits(const std::string &str)
    {
        return std::all_of(str.begin(), str.end(), [](const char e)
                           { return std::isdigit(e); });
    }

    bool allAlpha(const std::string_view str)
    {
        return std::all_of(str.begin(), str.end(), [](const char e)
                           { return std::isalpha(e); });
    }

    bool allDigits(const std::string_view str)
    {
        return std::all_of(str.begin(), str.end(), [](const char e)
                           { return std::isdigit(e); });
    }
    // helper type for the visitor #4
    template <class... Ts>
    struct overloaded : Ts...
    {
        using Ts::operator()...;
    };
    // explicit deduction guide (not needed as of C++20)
    template <class... Ts>
    overloaded(Ts...) -> overloaded<Ts...>;

}

#endif