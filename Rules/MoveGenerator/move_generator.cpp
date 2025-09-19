#include "./move_generator.h"
#include "../RayGenerator/ray_generator.h"
#include "../../Utils/utils.h"
#include "../../Utils/global.h"
#include <vector>

using std::int8_t;
using std::uint8_t;
using std::uint64_t;
using std::vector;

MoveGenerator::MoveGenerator() {
    const array<uint64_t, 64> n = RayGenerator::generateNMasks();
    const array<uint64_t, 64> ne = RayGenerator::generateNEMasks();
    const array<uint64_t, 64> e = RayGenerator::generateEMasks();
    const array<uint64_t, 64> se = RayGenerator::generateSEMasks();
    const array<uint64_t, 64> s = RayGenerator::generateSMasks();
    const array<uint64_t, 64> sw = RayGenerator::generateSWMasks();
    const array<uint64_t, 64> w = RayGenerator::generateWMasks();
    const array<uint64_t, 64> nw = RayGenerator::generateNWMasks();

    const array<uint64_t, 64> knightmoves = MoveGenerator::generateKnightTable();
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
*/

uint64_t MoveGenerator::generateBishopMoves(
    const uint8_t from, 
    const uint64_t opponentPieces, 
    const uint64_t friendlyPieces
) {
    uint64_t move;
    uint64_t mask;

    uint64_t neRay = ne[from];
    uint64_t seRay = se[from];
    uint64_t swRay = sw[from];
    uint64_t nwRay = nw[from];
    
    uint64_t neOpponentBlockers = neRay & opponentPieces;
    uint64_t seOpponentBlockers = seRay & opponentPieces;
    uint64_t swOpponentBlockers = swRay & opponentPieces;
    uint64_t nwOpponentBlockers = nwRay & opponentPieces;

    uint64_t neFriendlyBlockers = neRay & friendlyPieces;
    uint64_t seFriendlyBlockers = seRay & friendlyPieces;
    uint64_t swFriendlyBlockers = swRay & friendlyPieces;
    uint64_t nwFriendlyBlockers = nwRay & friendlyPieces;

    uint64_t neOpponentIndex = getBlocker(neOpponentBlockers, (uint8_t)Direction::NE);
    uint64_t seOpponentIndex = getBlocker(seOpponentBlockers, (uint8_t)Direction::SE);
    uint64_t swOpponentIndex = getBlocker(swOpponentBlockers, (uint8_t)Direction::SW);
    uint64_t nwOpponentIndex = getBlocker(nwOpponentBlockers, (uint8_t)Direction::NW);

    uint64_t neFriendlyIndex = getBlocker(neFriendlyBlockers, (uint8_t)Direction::NE) >> 7;
    uint64_t seFriendlyIndex = getBlocker(seFriendlyBlockers, (uint8_t)Direction::SE) << 9;
    uint64_t swFriendlyIndex = getBlocker(swFriendlyBlockers, (uint8_t)Direction::SW) << 7;
    uint64_t nwFriendlyIndex = getBlocker(nwFriendlyBlockers, (uint8_t)Direction::NW) >> 9;



    return 0ULL;
}

uint64_t MoveGenerator::generateRookMoves(
    const uint8_t from, 
    const uint64_t opponentPieces, 
    const uint64_t friendlyPieces
) {
    uint64_t move;
    uint64_t mask;

    return 0ULL;
}

uint64_t MoveGenerator::generateQueenMoves(
    const uint8_t from, 
    const uint64_t opponentPieces, 
    const uint64_t friendlyPieces
) {
    uint64_t move;
    uint64_t mask;

    return 0ULL;
}

uint64_t MoveGenerator::generateKingMoves(
    const uint8_t from, 
    const uint64_t opponentPieces, 
    const uint64_t friendlyPieces
) {
    uint64_t move;
    uint64_t mask;

    return 0ULL;
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

uint64_t MoveGenerator::maskRayAfterBlocker(const uint64_t ray, const uint64_t blocker, const uint8_t dir) {
    if (blocker == 0) return ray;

    switch ((Direction)dir) {
        case Direction::N:
        case Direction::NE:
        case Direction::E:
        case Direction::SE:
            return ray & ~(ray & ~blocker);
        case Direction::S:
        case Direction::SW:
        case Direction::W:
        case Direction::NW:
            return ray & ~(ray & ~blocker); 
        default:
            return ray;
    }
}

uint64_t MoveGenerator::getBlocker(const uint64_t bitboard, const uint8_t direction) {
    switch ((Direction)direction) {
        case Direction::N:
            return MoveGenerator::getRightMostBit(bitboard);
        case Direction::NE:
            return MoveGenerator::getRightMostBit(bitboard);
        case Direction::E:
            return MoveGenerator::getLeftMostBit(bitboard);
        case Direction::SE:
            return MoveGenerator::getLeftMostBit(bitboard);
        case Direction::S:
            return MoveGenerator::getLeftMostBit(bitboard);
        case Direction::SW:
            return MoveGenerator::getLeftMostBit(bitboard);
        case Direction::W:
            return MoveGenerator::getRightMostBit(bitboard);
        case Direction::NW:
            return MoveGenerator::getRightMostBit(bitboard);
        default:
            return 0ULL;
    }
}

uint64_t MoveGenerator::getRightMostBit(uint64_t bitboard) {
    return 1ULL << __builtin_ctzll(bitboard);
}

uint64_t MoveGenerator::getLeftMostBit(uint64_t bitboard) {
    return 1ULL << (63 - __builtin_clzll(bitboard));
}