#ifndef RULES_H
#define RULES_H

#include "../Player/player.h"
#include <array>
#include <memory>

class Board;

class Rules {
public:
    Rules(Board* board);

    Board* board;

    bool isLegalMove(const int32_t move);
    bool isInCheck();
    bool isInCheckmate();
    bool isInStalemate();
    bool isDraw();
    bool isMovingOwnPiece(const int32_t move);
};

#endif