#include "./move_generator.h"
#include "../../Utils/utils.h"
#include <vector>

using std::int8_t;
using std::uint8_t;
using std::uint64_t;
using std::vector;

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

array<uint64_t, 64> MoveGenerator::generateBishopTable(
    const array<uint64_t, 64>& ne,
    const array<uint64_t, 64>& se,
    const array<uint64_t, 64>& sw,
    const array<uint64_t, 64>& nw
) {
    array<uint64_t, 64> table;

    for (int square = 0; square < 64; square++) {
        int rank = square / 8;
        int file = square % 8;
        uint64_t rays = 0ULL;

        rays |= nw[square];
        rays |= sw[square];
        rays |= se[square];
        rays |= ne[square];

        table[square] = rays;
    }

    return table;
}

array<uint64_t, 64> MoveGenerator::generateRookTable(
    const array<uint64_t, 64>& n,
    const array<uint64_t, 64>& e,
    const array<uint64_t, 64>& s,
    const array<uint64_t, 64>& w
) {
    array<uint64_t, 64> table;

    for (int square = 0; square < 64; square++) {
        int rank = square / 8;
        int file = square % 8;
        uint64_t rays = 0ULL;

        rays |= n[square];
        rays |= e[square];
        rays |= s[square];
        rays |= w[square];

        table[square] = rays;
    }

    return table;
}

array<uint64_t, 64> MoveGenerator::generateQueenTable(
    const array<uint64_t, 64>& bishopmoves, 
    const array<uint64_t, 64>& rookmoves
) {
    array<uint64_t, 64> table;

    for (int square = 0; square < 64; square++) {
        table[square] = bishopmoves[square] | rookmoves[square];
    };

    return table;
}

array<uint64_t, 64> MoveGenerator::generateKingTable(
    const array<uint64_t, 64>& queenmoves
) {
    array<uint64_t, 64> table;

    for (int square = 0; square < 64; square++) {
        uint64_t from = Utils::indexToBitboard(square);
        uint64_t mask = 1ULL;
        
        mask |= (from << 9);
        mask |= (from >> 9);
        mask |= (from << 8);
        mask |= (from >> 8);
        mask |= (from << 7);
        mask |= (from >> 7);
        mask |= (from << 1);
        mask |= (from >> 1);

        table[square] = mask & queenmoves[square];
    }

    return table;
}

int getRightMostIndex(uint64_t moves) {
    return __builtin_ctzll(moves);
}

int getLeftMostIndex(uint64_t moves) {
    return 63 - __builtin_clzll(moves);
}