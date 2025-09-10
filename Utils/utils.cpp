#include <string>
#include "./enums.cpp"
using std::string;

std::string pieceTypeToString(PieceType type) {
    switch (type) {
        case PieceType::Pawn:   return "Pawn";
        case PieceType::Knight: return "Knight";
        case PieceType::Bishop: return "Bishop";
        case PieceType::Rook:   return "Rook";
        case PieceType::Queen:  return "Queen";
        case PieceType::King:   return "King";
        default:                return "Unknown";
    }
}

std::string colorToString(Color color) {
    return (color == Color::White) ? "White" : "Black";
}