#include "player.h"
#include "../Utils/utils.h"
#include "../Utils/global.h"
#include <iostream>

using std::uint8_t;
using std::uint64_t;

// array<uint8_t, 16> pieces;
// array<uint8_t, 64> lookup;
// array<uint8_t, 6> slidingPieces;

Player::Player(
    uint8_t color,
    vector<uint8_t> pawns,
    vector<uint8_t> knights,
    vector<uint8_t> bishops,
    vector<uint8_t> rooks,
    uint8_t queen,
    uint8_t king
) {
    this->color = color;
    
    lookup.fill(NO_PIECE);
    pieces.fill(NO_SQUARE);

    setPosition(pawns, knights, bishops, rooks, queen, king);
    
}

void Player::setPosition(
        vector<uint8_t> pawns,
        vector<uint8_t> knights,
        vector<uint8_t> bishops,
        vector<uint8_t> rooks,
        uint8_t queen,
        uint8_t king
) {
    setPiece(king, (uint8_t)PieceIndex::K);
    setPiece(queen, (uint8_t)PieceIndex::Q);
    
    for (uint8_t i = 0; i < 8; i++) {
        uint8_t correction = (uint8_t)PieceIndex::P1;
        i < pawns.size() ? setPiece(pawns[i], i + correction) : setPiece(NO_SQUARE, i + correction);
    }
    
    for (uint8_t i = 0; i < 2; i++) {
        uint8_t correction = (uint8_t)PieceIndex::N1;
        i < knights.size() ? setPiece(knights[i], i + correction) : setPiece(NO_SQUARE, i + correction);
    }
    
    for (uint8_t i = 0; i < 2; i++) {
        uint8_t correction = (uint8_t)PieceIndex::B1;
        i < bishops.size() ? setPiece(bishops[i], i + correction) : setPiece(NO_SQUARE, i + correction);
    }
    
    for (uint8_t i = 0; i < 2; i++) {
        uint8_t correction = (uint8_t)PieceIndex::R1;
        i < rooks.size() ? setPiece(rooks[i], i + correction) : setPiece(NO_SQUARE, i + correction);
    }
    
    occupiedSquares = 0ULL;
    for (uint8_t i : pieces) {
        occupiedSquares |= (1ULL << i);
    }
}

void Player::setPiece(uint8_t index, uint8_t pieceIndex) {
    this->pieces[pieceIndex] = index;
    this->lookup[index] = index == NO_SQUARE ? NO_PIECE : pieceIndex;
}