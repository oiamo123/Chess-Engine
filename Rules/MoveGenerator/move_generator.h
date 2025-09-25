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
    uint64_t getBetweenMove(uint8_t from, uint8_t to, uint8_t piece);
    tuple<uint64_t, uint64_t> getPawnMove(uint8_t from, uint8_t color);
    uint64_t getKnightMove(uint64_t from);
    uint64_t getKingMove(uint64_t from);

    private:
    alignas(64) static uint64_t raysN[64];
    alignas(64) static uint64_t raysNE[64];
    alignas(64) static uint64_t raysE[64];
    alignas(64) static uint64_t raysSE[64];
    alignas(64) static uint64_t raysS[64];
    alignas(64) static uint64_t raysSW[64];
    alignas(64) static uint64_t raysW[64];
    alignas(64) static uint64_t raysNW[64];

    alignas(64) static uint64_t knightmoves[64];
    alignas(64) static uint64_t kingmoves[64];
    alignas(64) static uint64_t pawnAttacksWhite[48];
    alignas(64) static uint64_t pawnAttacksBlack[48];
    alignas(64) static uint64_t pawnPushesWhite[48];
    alignas(64) static uint64_t pawnPushesBlack[48];
    array<array<array<uint64_t, 64>, 64>, 3> betweenTable;
    array<array<array<uint64_t, 64>, 2>, 2> pawnmoves;

    array<uint64_t, 64> generateKnightTable();
    array<uint64_t, 64> generateKingTable();
    array<array<array<uint64_t, 64>, 2>, 2> generatePawnTables();
    array<array<array<uint64_t, 64>, 64>, 3> generateBetweenTable();
    uint64_t rayBetween(uint8_t from, uint8_t to);
};

#endif