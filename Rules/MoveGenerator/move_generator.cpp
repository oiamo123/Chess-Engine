#include "./move_generator.h"
#include "../RayGenerator/ray_generator.h"
#include "../../Utils/utils.h"
#include "../../Utils/global.h"
#include <array>
#include <iostream>

using std::int8_t;
using std::uint8_t;
using std::uint64_t;
using std::array;

alignas(64) uint64_t MoveGenerator::raysN[64];
alignas(64) uint64_t MoveGenerator::raysNE[64];
alignas(64) uint64_t MoveGenerator::raysE[64];
alignas(64) uint64_t MoveGenerator::raysSE[64];
alignas(64) uint64_t MoveGenerator::raysS[64];
alignas(64) uint64_t MoveGenerator::raysSW[64];
alignas(64) uint64_t MoveGenerator::raysW[64];
alignas(64) uint64_t MoveGenerator::raysNW[64];
array<uint64_t, 64> MoveGenerator::knightmoves;
array<uint64_t, 64> MoveGenerator::kingmoves;

MoveGenerator::MoveGenerator() {
    auto nMasks = RayGenerator::generateNMasks();
    auto neMasks = RayGenerator::generateNEMasks();
    auto eMasks = RayGenerator::generateEMasks();
    auto seMasks = RayGenerator::generateSEMasks();
    auto sMasks = RayGenerator::generateSMasks();
    auto swMasks = RayGenerator::generateSWMasks();
    auto wMasks = RayGenerator::generateWMasks();
    auto nwMasks = RayGenerator::generateNWMasks();

    std::copy(nMasks.begin(), nMasks.end(), raysN);
    std::copy(neMasks.begin(), neMasks.end(), raysNE);
    std::copy(eMasks.begin(), eMasks.end(), raysE);
    std::copy(seMasks.begin(), seMasks.end(), raysSE);
    std::copy(sMasks.begin(), sMasks.end(), raysS);
    std::copy(swMasks.begin(), swMasks.end(), raysSW);
    std::copy(wMasks.begin(), wMasks.end(), raysW);
    std::copy(nwMasks.begin(), nwMasks.end(), raysNW);

    knightmoves = MoveGenerator::generateKnightTable();
    kingmoves = MoveGenerator::generateKingTable();
};

/*
All sliding pieces work on the exact same concept. But basically:
1. Pre generate all valid move from a square in a specific direction ie North, North East, East, South East etc etc
2. Take the opponent pieces and friendly pieces, and & them with the valid rays for that piece so Bishop -> NE, SE, SW, NW
3. Depending on the direction, the blocking piece will either be the biggest index or the smallest index, or in other words left most (lmb) or right most bit (rmb)
4. We can take the lmb or rmb, and create a mask so that either everything to the left or right of that bit is masked off, removing invalid moves in that direction.
-> https://goiamo.dev/notes/chess-engines/move-generation
*/

// ¯\_(ツ)_/¯
uint64_t MoveGenerator::generateKnightMoves(const uint8_t from) {
    return knightmoves[from];
};

uint64_t MoveGenerator::generateBishopMoves(
    const uint8_t from, 
    const uint64_t opponentPieces, 
    const uint64_t friendlyPieces
) {
    return getLegalMovesForRay<Direction::NE>(from, opponentPieces, friendlyPieces) |
        getLegalMovesForRay<Direction::SE>(from, opponentPieces, friendlyPieces) |
        getLegalMovesForRay<Direction::SW>(from, opponentPieces, friendlyPieces) |
        getLegalMovesForRay<Direction::NW>(from, opponentPieces, friendlyPieces);
};

uint64_t MoveGenerator::generateRookMoves(
    const uint8_t from, 
    const uint64_t opponentPieces, 
    const uint64_t friendlyPieces
) {
    return getLegalMovesForRay<Direction::N>(from, opponentPieces, friendlyPieces) |
        getLegalMovesForRay<Direction::E>(from, opponentPieces, friendlyPieces) |
        getLegalMovesForRay<Direction::S>(from, opponentPieces, friendlyPieces) |
        getLegalMovesForRay<Direction::W>(from, opponentPieces, friendlyPieces);
};

uint64_t MoveGenerator::generateQueenMoves(
    const uint8_t from, 
    const uint64_t opponentPieces, 
    const uint64_t friendlyPieces
) {    
    return getLegalMovesForRay<Direction::N>(from, opponentPieces, friendlyPieces) |
        getLegalMovesForRay<Direction::NE>(from, opponentPieces, friendlyPieces) |
        getLegalMovesForRay<Direction::E>(from, opponentPieces, friendlyPieces) |
        getLegalMovesForRay<Direction::SE>(from, opponentPieces, friendlyPieces) |
        getLegalMovesForRay<Direction::S>(from, opponentPieces, friendlyPieces) |
        getLegalMovesForRay<Direction::SW>(from, opponentPieces, friendlyPieces) |
        getLegalMovesForRay<Direction::W>(from, opponentPieces, friendlyPieces) |
        getLegalMovesForRay<Direction::NW>(from, opponentPieces, friendlyPieces);;
};

uint64_t MoveGenerator::generateKingMoves(
    const uint8_t from, 
    const uint64_t friendlyPieces
) {
    uint64_t moves = kingmoves[from];
    return moves &= ~friendlyPieces;
};

array<uint64_t, 64> MoveGenerator::generateKingTable() {
    array<uint64_t, 64> table;

    for (uint8_t square = 0; square < 64; square++) {
        uint64_t bit = 1ULL << square;
        uint64_t moves = 0ULL;

        moves |= (bit << 8);
        moves |= (bit >> 8);
        if (!(bit & FILE_H)) moves |= (bit << 1);
        if (!(bit & FILE_A)) moves |= (bit >> 1);
        if (!(bit & FILE_H)) moves |= (bit << 9);
        if (!(bit & FILE_A)) moves |= (bit << 7);
        if (!(bit & FILE_H)) moves |= (bit >> 7);
        if (!(bit & FILE_A)) moves |= (bit >> 9);

        table[square] = moves;
    }

    return table;
};

array<uint64_t, 64> MoveGenerator::generateKnightTable() {
    const array<int8_t, 8> knightMoves = { -10, -17, -15, -6, 6, 10, 15, 17 };
    array<uint64_t, 64> table;

    for (uint8_t square = 0; square < 64; square++) {
        uint64_t moves = 0ULL;
        uint8_t rank = square / 8;
        uint8_t file = square % 8;

        for (uint8_t move : knightMoves) {
            uint8_t targetSquare = square + move;
            uint8_t targetRank = targetSquare / 8;
            uint8_t targetFile = targetSquare % 8;

            if (targetSquare >= 0 && targetSquare < 64 &&
                abs(targetRank - rank) + abs(targetFile - file) == 3) 
            {
                moves |= Utils::indexToBitboard(targetSquare);
            }
        }

        table[square] = moves;
    }

    return table;
};

uint64_t MoveGenerator::getRightMostBit(uint64_t bitboard) {
    return bitboard & (~bitboard + 1);
};

uint64_t MoveGenerator::getLeftMostBit(uint64_t bitboard) {
    return bitboard ? (1ULL << (63 ^ __builtin_clzll(bitboard))) : 0;
};