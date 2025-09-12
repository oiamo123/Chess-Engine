#include <memory>
#include <iostream>
#include "./board.h"
#include "../Player/player.h"
#include "../Utils/global.h"
using std::cout;
using std::endl;
using std::string;

Board::Board() {
    this->whiteCanCastleK = 1;
    this->whiteCanCastleQ = 1;
    this->blackCanCastleK = 1;
    this->blackCanCastleQ = 1;

    this->board = 0xFFFF00000000FFFF;
    this->turn = 0;
}

void Board::create(const string* fen) {
    if (fen != nullptr) {
        // Parse FEN string
        return;
    }

    players[0] = std::make_unique<Player>(
        1, 
        0x0000000000000081ULL, 
        0x0000000000000042ULL, 
        0x0000000000000024ULL, 
        0x000000000000FF00ULL, 
        0x0000000000000008ULL, 
        0x0000000000000010ULL 
    );

    players[1] = std::make_unique<Player>(
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

    board = players[0]->getAllPieces() | players[1]->getAllPieces();
    turn = 0;
}

void Board::display() {
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            int square = rank * 8 + file;
            uint64_t mask = 1LL << square;
            string pieceChar = ".";

            if (players[(int)Color::White]->pieceBitboards[(int)PieceType::Pawn] & mask) pieceChar = "♙";
            else if (players[(int)Color::White]->pieceBitboards[(int)PieceType::Rook] & mask) pieceChar = "♖";
            else if (players[(int)Color::White]->pieceBitboards[(int)PieceType::Knight] & mask) pieceChar = "♘";
            else if (players[(int)Color::White]->pieceBitboards[(int)PieceType::Bishop] & mask) pieceChar = "♗";
            else if (players[(int)Color::White]->pieceBitboards[(int)PieceType::Queen] & mask) pieceChar = "♕";
            else if (players[(int)Color::White]->pieceBitboards[(int)PieceType::King] & mask) pieceChar = "♔";
            else if (players[(int)Color::Black]->pieceBitboards[(int)PieceType::Pawn] & mask) pieceChar = "♟";
            else if (players[(int)Color::Black]->pieceBitboards[(int)PieceType::Rook] & mask) pieceChar = "♜";
            else if (players[(int)Color::Black]->pieceBitboards[(int)PieceType::Knight] & mask) pieceChar = "♞";
            else if (players[(int)Color::Black]->pieceBitboards[(int)PieceType::Bishop] & mask) pieceChar = "♝";
            else if (players[(int)Color::Black]->pieceBitboards[(int)PieceType::Queen] & mask) pieceChar = "♛";
            else if (players[(int)Color::Black]->pieceBitboards[(int)PieceType::King] & mask) pieceChar = "♚";

            cout << pieceChar << " ";
        }
        cout << endl;
    }
}

void Board::move(int32_t move) {
    uint8_t color = (move >> 24) & MASK_8;
    uint8_t piece = (move >> 16) & MASK_8;
    uint8_t from  = (move >> 8)  & MASK_8;
    uint8_t to    = (move) & MASK_8;

    uint64_t fromMask = 1ULL << from;
    uint64_t toMask   = 1ULL << to;

    std::unique_ptr<Player>& player = players[color];

    // Update specific piece type
    player->pieceBitboards[piece] &= ~fromMask;
    player->pieceBitboards[piece] |= toMask;

    // Update global board
    board &= ~fromMask;
    board |= toMask;
}