#ifndef UTILS_H
#define UTILS_H
#include <string>
#include "../Pieces/Piece/piece.h"
using std::string;
using std::int8_t;

class Utils {
    public:
        static std::string getType(const int8_t type);
        static std::string getColor(const int8_t color);
        static std::string getSquare(const int8_t square);
        static void printBitboard(const uint64_t bitboard);
};

#endif