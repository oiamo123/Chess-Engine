#ifndef RULES_H
#define RULES_H

#include <array>
#include <cstdint>

using std::uint32_t;
using std::uint64_t;
using std::array;

class Board;
class MoveGenerator;

class Rules {
public:
    Rules(Board* board);
    Board* board;
    MoveGenerator* moveGenerator;

    bool isLegalMove(const uint32_t move);
    bool isInCheck();
    bool isInCheckmate();
    bool isInStalemate();
    bool isDraw();
    bool isMovingOwnPiece(const uint32_t move);
    uint64_t getMoves(const uint32_t moves);
};

#endif