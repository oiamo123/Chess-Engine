#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include <cstdint>
#include <array>

using std::uint64_t;
using std::array;

class MoveGenerator {
    public:
    MoveGenerator();
    uint64_t generateKnightMoves(const uint8_t from);
    uint64_t generateBishopMoves(const uint8_t from, const uint64_t opponentPieces, const uint64_t friendlyPieces);
    uint64_t generateRookMoves(const uint8_t from, const uint64_t opponentPieces, const uint64_t friendlyPieces);
    uint64_t generateQueenMoves(const uint8_t from, const uint64_t opponentPieces, const uint64_t friendlyPieces);
    uint64_t generateKingMoves(const uint8_t from, const uint64_t opponentPieces, const uint64_t friendlyPieces);
    
    private:
    array<uint64_t, 64> n;
    array<uint64_t, 64> ne;
    array<uint64_t, 64> e;
    array<uint64_t, 64> se;
    array<uint64_t, 64> s;
    array<uint64_t, 64> sw;
    array<uint64_t, 64> w;
    array<uint64_t, 64> nw;
    
    array<uint64_t, 64> knightmoves;
    array<uint64_t, 64> generateKnightTable();

    uint64_t maskRayAfterBlocker(const uint64_t ray, const uint64_t blocker, const uint8_t dir);
    uint64_t getBlocker(const uint64_t bitboard, uint8_t direction);
    uint64_t getRightMostBit(const uint64_t bitboard);
    uint64_t getLeftMostBit(const uint64_t bitboard);
};

#endif