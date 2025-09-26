#ifndef BOARD_H
#define BOARD_H

#include "../../Rules/MoveGenerator/move_generator.h"
#include "../Rules/rules.h"
#include <cstdint>
#include <string>
#include <array>

using std::string;
using std::array;
using std::uint8_t;
using std::uint32_t;
using std::uint64_t;

class Board {
    public:
    Board(const string fen);
    void move(const uint32_t move);
    
    private:
    Rules rules;
    MoveGenerator moveGenerator;
    
    array<Player, 2> players;
    uint8_t turn;
    uint64_t enPassantSquare;
    uint8_t halfMoves;
    uint8_t fullMoves;
    
    void display();
    void create(const string fen = "");
    void createPlayers(
        array<vector<uint8_t>, 6> whitePieces,
        array<vector<uint8_t>, 6> blackPieces
    );
    void setPinned();
};

#endif
