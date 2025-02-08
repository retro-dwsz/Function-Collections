/**
 * Types.hxx: A alias collection by @author David "Rétro" Siřait
 * Use this to simplify your journey
 *
 * You can freely edit this file
 * Contact me via discord @dwsz56
 *
 * As usual, this is not meant to be executed directly.
 *
 * Do not run or compile. Use it by importing.
 * Requires C++23 (-std=c++23)
 *
 * Compile: clang++ -std=c++23 -o <file> <file>.cpp -O3 -Wall -pedantic -pthread -mwindows -lgdi32 -luser32 -lws2_32 -W#warnings
 * -W#warnings and -mwindows are optional
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <any>

namespace TP{
    using STR = std::string;
    using SSTR = std::stringstream;
    using List = std::vector<std::any>;

    using VANY = std::vector<std::any>;
    using VINT = std::vector<int>;
    using VFLT = std::vector<float>;
    using VDBL = std::vector<double>;
    using VSTR = std::vector<std::string>;

    using MINT = std::map<int, int>;
    using MIST = std::map<int, TP::STR>;
    using MSTI = std::map<TP::STR, int>;
    using MSTR = std::map<TP::STR, TP::STR>;

    using MANY = std::map<std::any, std::any>;
    using DICT = MANY;

    using TINT = std::tuple<int, int>;
}
