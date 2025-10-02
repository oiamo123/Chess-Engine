#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include "../../Utils/global.h"
#include <functional>
#include <cstdint>
#include <array>
#include <tuple>

using std::uint64_t;
using std::array;
using std::function;
using std::tuple;

class MoveGenerator {  
    public:
    static void init();
    static inline array<uint64_t, 48> pawnAttacksWhite;
    static inline array<uint64_t, 48> pawnAttacksBlack;
    static inline array<uint64_t, 48> pawnPushesWhite;
    static inline array<uint64_t, 48> pawnPushesBlack;
    static inline array<uint64_t, 64> knightTable;
    static inline array<uint64_t, 64> bishopTable;
    static inline array<uint64_t, 64> rookTable;
    static inline array<uint64_t, 64> queenTable;
    static inline array<uint64_t, 64> kingTable;
    static inline array<uint64_t, 64> castlingTable;
    static inline array<array<array<uint64_t, 64>, 2>, 2> pawnTable;
    static inline array<array<array<uint64_t, 64>, 64>, 3> betweenTable;

    private:
    static array<uint64_t, 64> generateKnightTable();
    static array<uint64_t, 64> generateBishopTable(        
        array<uint64_t, 64> ne,
        array<uint64_t, 64> se,
        array<uint64_t, 64> sw,
        array<uint64_t, 64> nw
    );
    
    static array<uint64_t, 64> generateRookTable(
        array<uint64_t, 64> n,
        array<uint64_t, 64> e,
        array<uint64_t, 64> s,
        array<uint64_t, 64> w
    );
    
    static array<uint64_t, 64> generateQueenTable(
        array<uint64_t, 64> bishoptable,
        array<uint64_t, 64> rooktable
    );

    static array<uint64_t, 64> generateKingTable();
    static array<uint64_t, 64> generateCastlingMoves();
    static array<array<array<uint64_t, 64>, 2>, 2> generatePawnTables();
    static array<array<array<uint64_t, 64>, 64>, 3> generateBetweenTable();
    
    static uint64_t rayBetween(uint8_t from, uint8_t to);
};

#endif