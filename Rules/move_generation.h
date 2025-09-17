#ifndef MOVEGENERATION_H
#define MOVEGENERATION_H

#include <map>
#include <vector>
#include <cstdint>

using std::uint64_t;
using std::map;
using std::vector;

class MoveGenerator {
    public:
    typedef uint64_t (*IsValidMove)(uint64_t, int8_t);

    static map<uint64_t, uint64_t> generateKnightTable();
    static map<uint64_t, uint64_t> generateBishopTable();
    static map<uint64_t, uint64_t> generateRookTable();
    static map<uint64_t, uint64_t> generateQueenTable(
        const map<uint64_t, uint64_t>& bishopmoves, 
        const map<uint64_t, uint64_t>& rookmoves
    );
};

#endif