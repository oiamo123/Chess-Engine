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

class Board;
class Player;

class MoveGenerator {  
    public:
    MoveGenerator();
    tuple<uint64_t, uint64_t> getPawnMoves(uint8_t from, uint8_t color);
    uint64_t getKnightMoves(uint64_t from);
    uint64_t getBishopMoves(uint64_t from);
    uint64_t getRookMoves(uint64_t from);
    uint64_t getQueenMoves(uint64_t from);
    uint64_t getKingMoves(uint64_t from);
    tuple<uint64_t, uint8_t>  getCastlingMoves(uint64_t from);
    uint64_t getBetweenMoves(uint8_t from, uint8_t to, uint8_t piece);

    private:
    alignas(64) static uint64_t pawnAttacksWhite[48];
    alignas(64) static uint64_t pawnAttacksBlack[48];
    alignas(64) static uint64_t pawnPushesWhite[48];
    alignas(64) static uint64_t pawnPushesBlack[48];
    alignas(64) static uint64_t knightmoves[64];
    alignas(64) static uint64_t bishopmoves[64];
    alignas(64) static uint64_t rookmoves[64];
    alignas(64) static uint64_t queenmoves[64];
    alignas(64) static uint64_t kingmoves[64];
    alignas(64) static uint64_t castlingmoves[64];
    array<array<array<uint64_t, 64>, 2>, 2> pawnmoves;
    array<array<array<uint64_t, 64>, 64>, 3> betweenTable;

    array<uint64_t, 64> generateKnightTable();
    array<uint64_t, 64> generateBishopTable(        
        array<uint64_t, 64> ne,
        array<uint64_t, 64> se,
        array<uint64_t, 64> sw,
        array<uint64_t, 64> nw
    );
    
    array<uint64_t, 64> generateRookTable(
        array<uint64_t, 64> n,
        array<uint64_t, 64> e,
        array<uint64_t, 64> s,
        array<uint64_t, 64> w
    );
    
    array<uint64_t, 64> generateQueenTable(
        array<uint64_t, 64> bishoptable,
        array<uint64_t, 64> rooktable
    );

    array<uint64_t, 64> generateKingTable();
    array<uint64_t, 64> generateCastlingMoves();
    array<array<array<uint64_t, 64>, 2>, 2> generatePawnTables();
    array<array<array<uint64_t, 64>, 64>, 3> generateBetweenTable();
    
    uint64_t rayBetween(uint8_t from, uint8_t to);
};

#endif