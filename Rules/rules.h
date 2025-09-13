#ifndef RULES_H
#define RULES_H
#include "../Board/board.h"
#include "../Player/player.h"
#include <array>
#include <memory>

class Rules {
    public:
        static bool isLegalMove(const std::array<std::unique_ptr<Player>, 2>& players, const int32_t move);
        static bool isInCheck(const std::array<std::unique_ptr<Player>, 2>& players, const int playerColor);
        static bool isInCheckmate(const std::array<std::unique_ptr<Player>, 2>& players, const int playerColor);
        static bool isInStalemate(const std::array<std::unique_ptr<Player>, 2>& players, const int playerColor);
        static bool isDraw(const std::array<std::unique_ptr<Player>, 2>& players);
        static bool isMovingOwnPiece(const std::array<std::unique_ptr<Player>, 2>& players, const int32_t move);
};

#endif