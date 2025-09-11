#include <memory>
#include <iostream>
#include "./board.h"
#include "../Player/player.h"
#include "../Utils/global.h"
using std::cout;
using std::endl;
using std::string;

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

void Board::create(const string* fen) {
    if (fen != nullptr) {
        // Parse FEN string
        return;
    }

    white = std::make_unique<Player>(
        1, 
        0x0000000000000081ULL, 
        0x0000000000000042ULL, 
        0x0000000000000024ULL, 
        0x000000000000FF00ULL, 
        0x0000000000000008ULL, 
        0x0000000000000010ULL 
    );

    black = std::make_unique<Player>(
        -1, 
        0x8100000000000000ULL, 
        0x4200000000000000ULL, 
        0x2400000000000000ULL, 
        0x00FF000000000000ULL, 
        0x0800000000000000ULL, 
        0x1000000000000000ULL  
    );

    whiteCanCastleK = whiteCanCastleQ = 1;
    blackCanCastleK = blackCanCastleQ = 1;

    board = white->getAllPieces() | black->getAllPieces();
    turn = 0;
}

void Board::display() {
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            int square = rank * 8 + file;
            int64_t mask = 1LL << square;
            char pieceChar = '.';

            if (white->getPawns() & mask) pieceChar = 'P';
            else if (white->getRooks() & mask) pieceChar = 'R';
            else if (white->getKnights() & mask) pieceChar = 'N';
            else if (white->getBishops() & mask) pieceChar = 'B';
            else if (white->getQueen() & mask) pieceChar = 'Q';
            else if (white->getKing() & mask) pieceChar = 'K';
            else if (black->getPawns() & mask) pieceChar = 'p';
            else if (black->getRooks() & mask) pieceChar = 'r';
            else if (black->getKnights() & mask) pieceChar = 'n';
            else if (black->getBishops() & mask) pieceChar = 'b';
            else if (black->getQueen() & mask) pieceChar = 'q';
            else if (black->getKing() & mask) pieceChar = 'k';

            cout << pieceChar << " ";
        }
        cout << endl;
    }
}

void Board::move(const int32_t move) {
    uint8_t color = (move >> 24) & MASK_8;
    uint8_t piece = (move >> 16) & MASK_8;
    uint8_t from = (move >> 8) & MASK_8;
    uint8_t to = (move) & MASK_8;
}