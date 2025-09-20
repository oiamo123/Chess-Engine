#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <tuple>
#include "../Pieces/Piece/piece.h"

using std::string;
using std::uint8_t;
using std::uint64_t;
using std::tuple;

class Utils {
    public:
        static string getType(const uint8_t type);
        static string getColor(const uint8_t color);
        static string getSquare(const uint64_t square);
        static uint64_t indexToBitboard(const uint8_t index);
        static uint8_t bitboardToIndex(const uint64_t);
        static void printBitboard(const uint64_t bitboard);
        static tuple<uint8_t, uint8_t, uint8_t, uint8_t> parseMove(const uint32_t move);
        static uint32_t createMove(const uint8_t piece, const uint8_t color, const uint8_t from, const uint8_t to);
};

#endif