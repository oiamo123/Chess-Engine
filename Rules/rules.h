#ifndef RULES_H
#define RULES_H

#include "../Utils/global.h"
#include <array>
#include <cstdint>

using std::uint32_t;
using std::uint64_t;
using std::array;

class Board;
class MoveGenerator;
class Player;

class Rules {
    public:
    Rules(
        Player& white, 
        Player& black, 
        MoveGenerator& moveGenerator
    );
    
    bool IsLegalMove(uint32_t move);
    bool IsInCheck(uint64_t king);

    private:
    Player& white;
    Player& black;
    MoveGenerator& moveGenerator;

    template<PieceType pt, Color c = Color::White>
    __attribute__((always_inline)) inline bool isLegalMove(
        const uint8_t from, 
        const uint8_t to
    );

    bool isInCheck(uint8_t from, uint8_t to, Player cur, Player opposing);
    bool isInCheckmate();
    bool isInStalemate();
    bool isDraw();
};

#endif