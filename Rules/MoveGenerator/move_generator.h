#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include "../../Utils/global.h"
#include <functional>
#include <cstdint>
#include <array>

using std::uint64_t;
using std::array;
using std::function;

class MoveGenerator {
    public:
    MoveGenerator();

    uint64_t generateKnightMoves(const uint8_t from);
    uint64_t generateBishopMoves(const uint8_t from, const uint64_t opponentPieces, const uint64_t friendlyPieces);
    uint64_t generateRookMoves(const uint8_t from, const uint64_t opponentPieces, const uint64_t friendlyPieces);
    uint64_t generateQueenMoves(const uint8_t from, const uint64_t opponentPieces, const uint64_t friendlyPieces);
    uint64_t generateKingMoves(const uint8_t from, const uint64_t friendlyPieces);

    private:
    alignas(64) static uint64_t raysN[64];
    alignas(64) static uint64_t raysNE[64];
    alignas(64) static uint64_t raysE[64];
    alignas(64) static uint64_t raysSE[64];
    alignas(64) static uint64_t raysS[64];
    alignas(64) static uint64_t raysSW[64];
    alignas(64) static uint64_t raysW[64];
    alignas(64) static uint64_t raysNW[64];

    static array<uint64_t, 64> knightmoves;
    static array<uint64_t, 64> kingmoves;

    template<Direction dir>
    __attribute__((always_inline)) inline uint64_t getLegalMovesForRay(
        uint8_t from,
        uint64_t opponentPieces,
        uint64_t friendlyPieces
    );

    array<uint64_t, 64> generateKnightTable();
    array<uint64_t, 64> generateKingTable();

    uint64_t getRightMostBit(const uint64_t bitboard);
    uint64_t getLeftMostBit(const uint64_t bitboard);
};

#include "./get_legal_moves.tpp"

#endif