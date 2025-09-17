#ifndef RULES_H
#define RULES_H

#include "../Player/player.h"
#include <array>
#include <memory>
#include <map>
#include <vector>

using std::map;
using std::vector;

class Board;

class Rules {
public:
    Rules(Board* board);

    Board* board;
    map<uint64_t, uint64_t> knightmoves;
    map<uint64_t, uint64_t> rookmoves;
    map<uint64_t, uint64_t> bishopmoves;
    map<uint64_t, uint64_t> queenmoves;

    bool isLegalMove(const int32_t move);
    bool isInCheck();
    bool isInCheckmate();
    bool isInStalemate();
    bool isDraw();
    bool isMovingOwnPiece(const int32_t move);
    map<uint64_t, uint64_t> generateKnightTable();
};

#endif