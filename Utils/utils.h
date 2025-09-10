#ifndef UTILS_H
#define UTILS_H
#include <string>
#include "../Pieces/Piece/piece.h"
using std::string;
using std::int8_t;

enum class PieceType {
    Pawn = 1,
    Knight,
    Bishop,
    Rook,
    Queen,
    King
};

enum class Color {
    White = 1,
    Black
};

class Utils {
    public:
        static std::string pieceTypeToString(const int8_t type);
        static std::string colorToString(const int8_t color);
};

#endif