#include <memory>
#include <iostream>
#include "./board.h"
#include "../Player/player.cpp"
using std::cout;
using std::endl;

// Constructor
Board::Board() {
    white = std::make_unique<Player>();
    black = std::make_unique<Player>();

    whiteCanCastleK = 1;
    whiteCanCastleQ = 1;
    blackCanCastleK = 1;
    blackCanCastleQ = 1;

    board = 0xFFFF00000000FFFF;
    turn = 0;
}

void Board::create(const std::string* fen = nullptr) {
    if (fen != nullptr) {
        // Parse FEN string
        return;
    } 

    whiteCanCastleK = 1;
    whiteCanCastleQ = 1;
    blackCanCastleK = 1;
    blackCanCastleQ = 1;

    board = 0xFFFF00000000FFFF;
    turn = 0;
}

void Board::display() {
    cout << "Board state:" << endl;
}