#include <memory>
#include <iostream>
#include "./board.h"
#include "../Player/player.cpp"
using std::cout;
using std::endl;

// Constructor
Board::Board() {
    white = nullptr;
    black = nullptr;

    whiteCanCastleK = 1;
    whiteCanCastleQ = 1;
    blackCanCastleK = 1;
    blackCanCastleQ = 1;

    board = 0xFFFF00000000FFFF;
    turn = 0;
}

void Board::create(const std::string* fen) {
    if (fen != nullptr) {
        // Parse FEN string
        return;
    } 

    white = std::make_unique<Player>(
        1, 
        0x81,       // Rooks
        0x42,       // Knights
        0x24,       // Bishops
        0xFF00,     // Pawns
        0x8,        // Queen
        0x10        // King
    );

    black = std::make_unique<Player>(
        -1, 
        0x8100000000000000, // Rooks
        0x4200000000000000, // Knights
        0x2400000000000000, // Bishops
        0xFF00000000000000, // Pawns
        0x800000000000000,  // Queen
        0x1000000000000000  // King
    );

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