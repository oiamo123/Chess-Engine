#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include <cstdint>
#include <array>

using std::uint64_t;
using std::array;

class MoveGenerator {
    public:
    static array<uint64_t, 64> generateKnightTable();
    static array<uint64_t, 64> generateBishopTable(
        const array<uint64_t, 64>& ne,
        const array<uint64_t, 64>& se,
        const array<uint64_t, 64>& sw,
        const array<uint64_t, 64>& nw
    );

    static array<uint64_t, 64> generateRookTable(
        const array<uint64_t, 64>& n,
        const array<uint64_t, 64>& e,
        const array<uint64_t, 64>& s,
        const array<uint64_t, 64>& w
    );

    static array<uint64_t, 64> generateQueenTable(
        const array<uint64_t, 64>& bishopmoves, 
        const array<uint64_t, 64>& rookmoves
    );

    static array<uint64_t, 64> generateKingTable(
        const array<uint64_t, 64>& queenmoves
    );
};

#endif