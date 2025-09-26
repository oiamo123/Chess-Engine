#include "player.h"
#include "../Utils/utils.h"
#include "../Utils/global.h"
using std::uint8_t;
using std::uint64_t;

// array<uint8_t, 16> pieces;
// array<uint8_t, 64> lookup;
// array<uint8_t, 6> slidingPieces;

Player::Player(
        uint8_t color,
        array<uint8_t, 8> pawns,
        array<uint8_t, 2> knights,
        array<uint8_t, 2> bishops,
        array<uint8_t, 2> rooks,
        uint8_t queen,
        uint8_t king
) {
    setPosition(pawns, knights, bishops, rooks, queen, king);
    this->color = color;
}

void Player::setPosition(
        array<uint8_t, 8> pawns,
        array<uint8_t, 2> knights,
        array<uint8_t, 2> bishops,
        array<uint8_t, 2> rooks,
        uint8_t queen,
        uint8_t king
) {
    setPiece(king, (uint8_t)PieceIndex::K);
    setPiece(queen, (uint8_t)PieceIndex::Q);
    
    for (uint8_t i = 0; i < 8; i++) {
        i < pawns.size() ? setPiece(pawns[i], i) : setPiece(NO_SQUARE, i);
    }
    
    for (uint8_t i = 0; i < 2; i++) {
        i < knights.size() ? setPiece(knights[i], i) : setPiece(NO_SQUARE, i);
    }
    
    for (uint8_t i = 0; i < 2; i++) {
        i < bishops.size() ? setPiece(bishops[i], i) : setPiece(NO_SQUARE, i);
    }
    
    for (uint8_t i = 0; i < 2; i++) {
        i < rooks.size() ? setPiece(rooks[i], i) : setPiece(NO_SQUARE, i);
    }
    
    occupiedSquares = 0ULL;
    for (uint8_t i : pieces) {
        occupiedSquares |= (1ULL << i);
    }
}

void Player::setPiece(uint8_t index, uint8_t pieceIndex) {
    this->pieces[pieceIndex] = index;
    if (index != NO_SQUARE) {
        this->lookup[index] = pieceIndex;
    }
}