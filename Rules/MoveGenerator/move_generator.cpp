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

MoveGenerator::MoveGenerator() {
    rays[(uint8_t)Direction::N] = RayGenerator::generateNMasks(); 
    rays[(uint8_t)Direction::NE] = RayGenerator::generateNEMasks();
    rays[(uint8_t)Direction::E] = RayGenerator::generateEMasks();
    rays[(uint8_t)Direction::SE] = RayGenerator::generateSEMasks();
    rays[(uint8_t)Direction::S] = RayGenerator::generateSMasks();
    rays[(uint8_t)Direction::SW] = RayGenerator::generateSWMasks();
    rays[(uint8_t)Direction::W] = RayGenerator::generateWMasks();
    rays[(uint8_t)Direction::NW] = RayGenerator::generateNWMasks();
    n = RayGenerator::generateNMasks();

    const array<uint64_t, 64> knightmoves = MoveGenerator::generateKnightTable();
    const array<uint64_t, 64> kingmoves = MoveGenerator::generateKingTable();
}

// ¯\_(ツ)_/¯
uint64_t MoveGenerator::generateKnightMoves(const uint8_t from) {
    return knightmoves[from];
}

/*
All sliding pieces work on the exact same concept. But basically:
1. Pre generate all valid move from a square in a specific direction ie North, North East, East, South East etc etc
2. Take the opponent pieces and friendly pieces, and & them with the valid rays for that piece so Bishop -> NE, SE, SW, NW
3. Depending on the direction, the blocking piece will either be the biggest index or the smallest index, or in other words left most (lmb) or right most bit (rmb)
4. We can take the lmb or rmb, and create a mask so that either everything to the left or right of that bit is masked off, removing invalid moves in that direction.
-> https://goiamo.dev/notes/chess-engines/move-generation
*/

uint64_t MoveGenerator::generateBishopMoves(
    const uint8_t from, 
    const uint64_t opponentPieces, 
    const uint64_t friendlyPieces
) {
    uint64_t moves = 0ULL;
    array<Direction, 4> directions = { 
        Direction::NE, 
        Direction::SE,
        Direction::SW, 
        Direction::NW 
    };

    for (Direction direction : directions) {
        moves |= getLegalMovesForRay(direction, from, opponentPieces, friendlyPieces);
    };

    return moves;
}

uint64_t MoveGenerator::generateRookMoves(
    const uint8_t from, 
    const uint64_t opponentPieces, 
    const uint64_t friendlyPieces
) {
    uint64_t moves = 0ULL;
    array<Direction, 4> directions = { 
        Direction::N, 
        Direction::E, 
        Direction::S, 
        Direction::W 
    };

    for (Direction direction : directions) {
        moves |= getLegalMovesForRay(direction, from, opponentPieces, friendlyPieces);
    };

    return moves;
}

uint64_t MoveGenerator::generateQueenMoves(
    const uint8_t from, 
    const uint64_t opponentPieces, 
    const uint64_t friendlyPieces
) {
    uint64_t queenmoves = 0ULL;
    queenmoves |= generateRookMoves(from, opponentPieces, friendlyPieces);
    queenmoves |= generateBishopMoves(from, opponentPieces, friendlyPieces);
    return queenmoves;
}

uint64_t MoveGenerator::generateKingMoves(
    const uint8_t from, 
    const uint64_t friendlyPieces
) {
    uint64_t moves = kingmoves[from];
    return moves &= ~friendlyPieces;
}

array<uint64_t, 64> MoveGenerator::generateKingTable() {
    array<uint64_t, 64> table;

    for (uint8_t square = 0; square < 63; square++) {
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
}

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
}

// Gets the right most or left most bit
uint64_t MoveGenerator::nearestBlocker(const Direction direction, const uint64_t bitboard) {
    switch (direction) {
        case Direction::N:
        case Direction::NE:
        case Direction::E:
        case Direction::SE:
            return getRightMostBit(bitboard);

        case Direction::S:
        case Direction::SW:
        case Direction::W:
        case Direction::NW:
            return getLeftMostBit(bitboard);
    }
    
    return 0ULL;
}

// Corrections for friendly pieces
uint64_t MoveGenerator::beyondBlocker(const Direction direction, const uint64_t blocker) {
    switch (direction) {
        case Direction::N:  return blocker >> 8; 
        case Direction::NE: return blocker >> 9; 
        case Direction::E:  return blocker >> 1; 
        case Direction::SE: return blocker << 7; 
        case Direction::S:  return blocker << 8; 
        case Direction::SW: return blocker << 9; 
        case Direction::W:  return blocker << 1; 
        case Direction::NW: return blocker >> 7; 
    }
    return 0ULL;
}

// Gets the right most or left most bit between friendly and opponent pieces
uint64_t MoveGenerator::getLegalMovesForRay(
    Direction direction,
    uint8_t from,
    uint64_t opponentPieces,
    uint64_t friendlyPieces
) {
    uint64_t ray = rays[(uint8_t)direction][from];
    uint64_t opponentBlocker = nearestBlocker(direction, ray & opponentPieces);
    uint64_t friendlyBlocker = beyondBlocker(direction, nearestBlocker(direction, ray & friendlyPieces));
    uint64_t combinedBlocker = opponentBlocker | friendlyBlocker;

    if (!combinedBlocker) {
        return ray;
    }

    uint64_t blocker = nearestBlocker(direction, combinedBlocker);

    if (!blocker) return ray;

    int blockerIndex = Utils::bitboardToIndex(blocker);

    switch (direction) {
        case Direction::N:
        case Direction::NE:
        case Direction::E:
        case Direction::NW:
            return ray & ((blocker - 1) | blocker);
        
        case Direction::SE:
        case Direction::S:
        case Direction::SW:
        case Direction::W:
            return ray & ~(blocker - 1);
    }
    
    return 0ULL;
}

uint64_t MoveGenerator::getRightMostBit(uint64_t bitboard) {
    return bitboard & -bitboard;
}

uint64_t MoveGenerator::getLeftMostBit(uint64_t bitboard) {
    if (bitboard == 0) return 0ULL;
    int index = 63 - __builtin_clzll(bitboard);
    return 1ULL << index;
}