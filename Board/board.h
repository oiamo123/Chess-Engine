#ifndef BOARD_H
#define BOARD_H
#include "../Pieces/Piece/piece.h"
#include "../Player/player.h"
#include <cstdint>
#include <string>
#include <memory>
using std::uint64_t;
using std::int8_t;
using std::string;

class Board {
public:
    std::unique_ptr<Player> players[2];

    int8_t whiteCanCastleK;
    int8_t whiteCanCastleQ;
    int8_t blackCanCastleK;
    int8_t blackCanCastleQ;

    uint64_t board;
    int8_t turn;

    Board();
    void display();
    void create(const string* fen = nullptr);
    void createPieces();
    void move(const int32_t move);
};

#endif
