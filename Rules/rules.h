#ifndef RULES_H
#define RULES_H

#include <array>
#include <cstdint>

using std::uint32_t;
using std::uint64_t;
using std::array;

class Board;

class Rules {
public:
    Rules(Board* board);

    Board* board;

    array<uint64_t, 64> n;
    array<uint64_t, 64> ne;
    array<uint64_t, 64> e;
    array<uint64_t, 64> se;
    array<uint64_t, 64> s;
    array<uint64_t, 64> sw;
    array<uint64_t, 64> w;
    array<uint64_t, 64> nw;

    array<uint64_t, 64> knightmoves;
    array<uint64_t, 64> rookmoves;
    array<uint64_t, 64> bishopmoves;
    array<uint64_t, 64> queenmoves;

    bool isLegalMove(const uint32_t move);
    bool isInCheck();
    bool isInCheckmate();
    bool isInStalemate();
    bool isDraw();
    bool isMovingOwnPiece(const uint32_t move);
};

#endif