#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

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
    static map<uint64_t, uint64_t> generateBishopTable(
        const map<uint64_t, uint64_t>& ne,
        const map<uint64_t, uint64_t>& se,
        const map<uint64_t, uint64_t>& sw,
        const map<uint64_t, uint64_t>& nw
    );

    static map<uint64_t, uint64_t> generateRookTable(
        const map<uint64_t, uint64_t>& n,
        const map<uint64_t, uint64_t>& e,
        const map<uint64_t, uint64_t>& s,
        const map<uint64_t, uint64_t>& w
    );

    static map<uint64_t, uint64_t> generateQueenTable(
        const map<uint64_t, uint64_t>& bishopmoves, 
        const map<uint64_t, uint64_t>& rookmoves
    );

    static map<uint64_t, uint64_t> generateKingTable(
        const map<uint64_t, uint64_t>& queenmoves
    );
};

#endif