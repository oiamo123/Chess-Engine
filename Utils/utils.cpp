#include <string>
#include "./utils.h"
using std::string;
using std::int8_t;

string Utils::pieceTypeToString(const int8_t type) {
    switch (type) {
        case static_cast<int8_t>(PieceType::Pawn):   return "Pawn";
        case static_cast<int8_t>(PieceType::Knight): return "Knight";
        case static_cast<int8_t>(PieceType::Bishop): return "Bishop";
        case static_cast<int8_t>(PieceType::Rook):   return "Rook";
        case static_cast<int8_t>(PieceType::Queen):  return "Queen";
        case static_cast<int8_t>(PieceType::King):   return "King";
        default:                                      return "Unknown";
    }
}

string Utils::colorToString(const int8_t color) {
    return (color == static_cast<int8_t>(Color::White)) ? "White" : "Black";
}