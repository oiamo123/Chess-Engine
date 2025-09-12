#include <string>
#include <iostream>
#include "./utils.h"
#include "./global.h"
using std::cout;
using std::endl;
using std::string;
using std::int8_t;

string Utils::getType(const int8_t type) {
    switch (type) {
        case static_cast<int8_t>(PieceType::Pawn): return "Pawn";
        case static_cast<int8_t>(PieceType::Knight): return "Knight";
        case static_cast<int8_t>(PieceType::Bishop): return "Bishop";
        case static_cast<int8_t>(PieceType::Rook): return "Rook";
        case static_cast<int8_t>(PieceType::Queen): return "Queen";
        case static_cast<int8_t>(PieceType::King): return "King";
        default: return "Unknown";
    }
}

string Utils::getColor(const int8_t color) {
    return (color == static_cast<int8_t>(Color::White)) ? "White" : "Black";
}

string Utils::getSquare(const uint64_t square) {
    if (square == 0) return "??";

    int file = __builtin_ctzll(square) % 8;
    int rank = __builtin_ctzll(square) / 8;

    char fileChar = 'a' + file;
    char rankChar = '1' + rank;

    return string(1, fileChar) + string(1, rankChar);
}

void Utils::printBitboard(const uint64_t bitboard) {
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            int square = rank * 8 + file;
            if (bitboard & (1ULL << square)) {
                cout << "1 ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

uint64_t Utils::indexToBitboard(const int8_t index) {
    if (index < 0 || index > 63) {
        return 0;
    }

    return 1ULL << index;
}