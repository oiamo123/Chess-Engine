#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include "../../Utils/global.h"
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
    uint64_t generateKingMoves(const uint8_t from, const uint64_t friendlyPieces);
    array<array<uint64_t, 64>, 8> rays;     
    array<uint64_t, 64> n;
    
    private:
    array<uint64_t, 64> knightmoves;
    array<uint64_t, 64> kingmoves;
    
    array<uint64_t, 64> generateKnightTable();
    array<uint64_t, 64> generateKingTable();
    
    uint64_t nearestBlocker(const Direction direction, const uint64_t bitboard);
    uint64_t beyondBlocker(const Direction direction, const uint64_t blocker);
    uint64_t getLegalMovesForRay(
        const Direction direction, 
        const uint8_t from, 
        const uint64_t opponentPieces, 
        const uint64_t friendlyPieces
    );
    int64_t maskBlocker(const uint8_t index, const uint64_t moves);

    uint64_t getRightMostBit(const uint64_t bitboard);
    uint64_t getLeftMostBit(const uint64_t bitboard);
};

#endif