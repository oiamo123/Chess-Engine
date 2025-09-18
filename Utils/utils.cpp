#include <string>
#include <iostream>
#include "./utils.h"
#include "./global.h"
using std::cout;
using std::endl;
using std::string;
using std::uint8_t;

string Utils::getType(const uint8_t type) {
    switch (type) {
        case static_cast<uint8_t>(PieceType::Pawn): return "Pawn";
        case static_cast<uint8_t>(PieceType::Knight): return "Knight";
        case static_cast<uint8_t>(PieceType::Bishop): return "Bishop";
        case static_cast<uint8_t>(PieceType::Rook): return "Rook";
        case static_cast<uint8_t>(PieceType::Queen): return "Queen";
        case static_cast<uint8_t>(PieceType::King): return "King";
        default: return "Unknown";
    }
}

string Utils::getColor(const uint8_t color) {
    return (color == static_cast<uint8_t>(Color::White)) ? "White" : "Black";
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

uint64_t Utils::indexToBitboard(const uint8_t index) {
    if (index > 63) {
        return 0;
    }

    return 1ULL << index;
}

tuple<uint8_t, uint8_t, uint8_t, uint8_t> Utils::parseMove(const uint32_t move) {
    uint8_t piece = (move >> 24) & MASK_8;
    uint8_t color = (move >> 16) & MASK_8;
    uint8_t from = (move >> 8) & MASK_8;
    uint8_t to = move & MASK_8;

    return { piece, color, from, to };
}

uint32_t Utils::createMove(const uint8_t piece, const uint8_t color, const uint8_t from, const uint8_t to) {
    int32_t move = 0;
    move |= (uint8_t)piece << 24;
    move |= (uint8_t)color << 16;
    move |= (uint8_t)from << 8;
    move |= (uint8_t)to;

    return move;
}