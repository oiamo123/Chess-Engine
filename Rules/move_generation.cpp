#include "./move_generation.h"
#include "../Utils/utils.h"
#include <vector>

using std::vector;

map<uint64_t, uint64_t> MoveGenerator::generateKnightTable() {
    const vector<int8_t> knightMoves = { -10, -17, -15, -6, 6, 10, 15, 17 };

    map<uint64_t, uint64_t> table;

    for (int8_t square = 0; square < 64; square++) {
        uint64_t moves = 0ULL;
        int8_t rank = square / 8;
        int8_t file = square % 8;

        for (int8_t move : knightMoves) {
            int8_t targetSquare = square + move;
            int8_t targetRank = targetSquare / 8;
            int8_t targetFile = targetSquare % 8;

            if (targetSquare >= 0 && targetSquare < 64 &&
                abs(targetRank - rank) + abs(targetFile - file) == 3) 
            {
                moves |= Utils::indexToBitboard(targetSquare);
            }
        }
        table[1LL << square] = moves;
    }

    return table;
}

map<uint64_t, uint64_t> MoveGenerator::generateBishopTable() {
    map<uint64_t, uint64_t> table;

    for (int square = 0; square < 64; square++) {
        uint64_t from = 1ULL << square;
        int rank = square / 8;
        int file = square % 8;
        uint64_t rays = 0ULL;

        for (int r = rank + 1, f = file + 1; r < 8 && f < 8; r++, f++) {
            rays |= Utils::indexToBitboard((r * 8 + f));
        }

        for (int r = rank + 1, f = file - 1; r < 8 && f >= 0; r++, f--) {
            rays |= Utils::indexToBitboard((r * 8 + f));
        }

        for (int r = rank - 1, f = file + 1; r >= 0 && f < 8; r--, f++) {
            rays |= Utils::indexToBitboard((r * 8 + f));
        }

        for (int r = rank - 1, f = file - 1; r >= 0 && f >= 0; r--, f--) {
            rays |= Utils::indexToBitboard((r * 8 + f));
        }

        table[from] = rays;
    }

    return table;
}

map<uint64_t, uint64_t> MoveGenerator::generateRookTable() {
    map<uint64_t, uint64_t> table;

    for (int square = 0; square < 64; square++) {
        uint64_t from = 1ULL << square;
        int rank = square / 8;
        int file = square % 8;
        uint64_t rays = 0ULL;

        for (int r = rank + 1; r < 8; r++) {
            rays |= Utils::indexToBitboard((r * 8 + file));
        }

        for (int r = rank - 1; r >= 0; r--) {
            rays |= Utils::indexToBitboard((r * 8 + file));
        }

        for (int f = file + 1; f < 8; f++) {
            rays |= Utils::indexToBitboard((rank * 8 + f));
        }

        for (int f = file - 1; f >= 0; f--) {
            rays |= Utils::indexToBitboard((rank * 8 + f));
        }

        table[from] = rays;
    }

    return table;
}

map<uint64_t, uint64_t> MoveGenerator::generateQueenTable(
    const map<uint64_t, uint64_t>& bishopmoves, 
    const map<uint64_t, uint64_t>& rookmoves
) {
    map<uint64_t, uint64_t> table;

    for (int square = 0; square < 64; square++) {
        uint64_t from = Utils::indexToBitboard(square);
        table[from] = bishopmoves.at(from) | rookmoves.at(from);
    };

    return table;
}