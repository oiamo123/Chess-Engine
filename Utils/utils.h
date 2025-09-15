#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <tuple>
#include "../Pieces/Piece/piece.h"

using std::string;
using std::int8_t;
using std::uint64_t;
using std::tuple;

class Utils {
    public:
        static string getType(const int8_t type);
        static string getColor(const int8_t color);
        static string getSquare(const uint64_t square);
        static uint64_t indexToBitboard(const int8_t index);
        static void printBitboard(const uint64_t bitboard);
        static tuple<int8_t, int8_t, int8_t, int8_t> parseMove(const int32_t move);
        static int32_t createMove(const int8_t piece, const int8_t color, const int8_t from, const int8_t to);
};

#endif