#ifndef UTILS_H
#define UTILS_H
#include <string>
#include "../Pieces/Piece/piece.h"
using std::string;
using std::int8_t;
using std::uint64_t;

class Utils {
    public:
        static std::string getType(const int8_t type);
        static std::string getColor(const int8_t color);
        static std::string getSquare(const uint64_t square);
        static uint64_t indexToBitboard(const int8_t index);
        static void printBitboard(const uint64_t bitboard);
};

#endif