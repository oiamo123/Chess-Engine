#ifndef RULES_H
#define RULES_H

#include "./MoveGenerator/move_generator.h"
#include "../Player/player.h"
#include "../Utils/global.h"
#include <array>
#include <cstdint>

using std::array;
using std::uint8_t;
using std::uint32_t;
using std::uint64_t;

class MoveGenerator;
class Player;

class Rules {
    public:
    Rules(
        Player& white, 
        Player& black
    );
    
    bool IsLegalMove(
        uint8_t piece,
        uint8_t color,
        uint8_t from,
        uint8_t to
    );

    private:
    Player& white;
    Player& black;

    bool isInCheck(
        uint8_t piece,
        uint8_t square,
        Player& friendly,
        Player& opposing
    );
    
    bool isInCheckmate();
    bool isInStalemate();
    bool isDraw();
    bool IsInCheck(uint64_t king);

    private:
    bool isThreatened(uint8_t square, Player& friendly, Player& opposing);
};

#endif