#include "./move_generator.h"
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

map<uint64_t, uint64_t> MoveGenerator::generateBishopTable(
    const map<uint64_t, uint64_t>& ne,
    const map<uint64_t, uint64_t>& se,
    const map<uint64_t, uint64_t>& sw,
    const map<uint64_t, uint64_t>& nw
) {
    map<uint64_t, uint64_t> table;

    for (int square = 0; square < 64; square++) {
        uint64_t from = 1ULL << square;
        int rank = square / 8;
        int file = square % 8;
        uint64_t rays = 0ULL;

        rays |= nw.at(from);
        rays |= sw.at(from);
        rays |= se.at(from);
        rays |= ne.at(from);

        table[from] = rays;
    }

    return table;
}

map<uint64_t, uint64_t> MoveGenerator::generateRookTable(
    const map<uint64_t, uint64_t>& n,
    const map<uint64_t, uint64_t>& e,
    const map<uint64_t, uint64_t>& s,
    const map<uint64_t, uint64_t>& w
) {
    map<uint64_t, uint64_t> table;

    for (int square = 0; square < 64; square++) {
        uint64_t from = 1ULL << square;
        int rank = square / 8;
        int file = square % 8;
        uint64_t rays = 0ULL;

        rays |= n.at(from);
        rays |= e.at(from);
        rays |= s.at(from);
        rays |= w.at(from);

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

map<uint64_t, uint64_t> MoveGenerator::generateKingTable(
    const map<uint64_t, uint64_t>& queenmoves
) {
    map<uint64_t, uint64_t> table;

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

        table[from] = mask & queenmoves.at(from);
    }

    return table;
}