#ifndef UTILS_H
#define UTILS_H

#include "./global.h"
#include <tuple>
#include <array>
#include <string>

using std::tuple;
using std::array;
using std::string;
using std::uint8_t;
using std::uint32_t;
using std::uint64_t;

class Player;

class Utils {
    public:
        static void parseFen(const string& fen, FenParams& fenParams);
        
        static string getDirection(const uint8_t direction);
        static string getType(const uint8_t type);
        static string getColor(const uint8_t color);
        static string getSquare(const uint64_t square);
        static bool sameRank(const uint8_t from, const uint8_t to);
        static bool sameFile(const uint8_t from, const uint8_t to);
        static bool sameDiagonal(const uint8_t from, const uint8_t to);
        static uint64_t indexToBitboard(const uint8_t index);
        static uint8_t bitboardToIndex(const uint64_t);
        static void printBitboard(const uint64_t bitboard);
        static tuple<uint8_t, uint8_t, uint8_t, uint8_t> parseMove(const uint32_t move);
        static uint32_t createMove(const uint8_t piece, const uint8_t color, const uint8_t from, const uint8_t to);
};

#endif