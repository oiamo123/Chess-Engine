#ifndef BOARD_H
#define BOARD_H

#include "../Pieces/Piece/piece.h"
#include "../Player/player.h"
#include "../Rules/rules.h"
#include <cstdint>
#include <string>

using std::uint8_t;
using std::uint32_t;
using std::uint64_t;
using std::string;

class Board {
public:
    Board();

    Rules rules;
    array<Player, 2> players;
    MoveGenerator moveGenerator;
    uint8_t turn;

    void display();
    void create(const string fen = "");
    void move(const uint32_t move);
};

#endif
