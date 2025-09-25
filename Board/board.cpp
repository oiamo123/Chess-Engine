#include <iostream>
#include "./board.h"
#include "../Player/player.h"
#include "../Utils/utils.h"
#include "../Utils/global.h"
#include "../Rules/rules.h"

using std::cout;
using std::endl;
using std::string;
using std::tuple;
using std::uint8_t;
using std::uint32_t;
using std::uint64_t;

Board::Board() : rules(this->players[0], this->players[1], this->moveGenerator) {}

void Board::create(const string fen) {
    if (fen != "") {
        // Parse FEN string
        return;
    }

    players[(uint8_t)Color::White].setPosition(
        1, 
        0x0000000000000081ULL, 
        0x0000000000000042ULL, 
        0x0000000000000024ULL, 
        0x000000000000FF00ULL, 
        0x0000000000000008ULL, 
        0x0000000000000010ULL 
    );

    players[(uint8_t)Color::Black].setPosition(
        -1, 
        0x8100000000000000ULL, 
        0x4200000000000000ULL, 
        0x2400000000000000ULL, 
        0x00FF000000000000ULL, 
        0x0800000000000000ULL, 
        0x1000000000000000ULL  
    );

    turn = 0;
}

void Board::display() {
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            int square = rank * 8 + file;
            uint64_t mask = 1LL << square;
            string pieceChar = ".";

            if (players[(uint8_t)Color::Black].pieceBitboards[(int)PieceType::Pawn] & mask) pieceChar = "♙";
            else if (players[(uint8_t)Color::Black].pieceBitboards[(int)PieceType::Rook] & mask) pieceChar = "♖";
            else if (players[(uint8_t)Color::Black].pieceBitboards[(int)PieceType::Knight] & mask) pieceChar = "♘";
            else if (players[(uint8_t)Color::Black].pieceBitboards[(int)PieceType::Bishop] & mask) pieceChar = "♗";
            else if (players[(uint8_t)Color::Black].pieceBitboards[(int)PieceType::Queen] & mask) pieceChar = "♕";
            else if (players[(uint8_t)Color::Black].pieceBitboards[(int)PieceType::King] & mask) pieceChar = "♔";
            else if (players[(uint8_t)Color::White].pieceBitboards[(int)PieceType::Pawn] & mask) pieceChar = "♟";
            else if (players[(uint8_t)Color::White].pieceBitboards[(int)PieceType::Rook] & mask) pieceChar = "♜";
            else if (players[(uint8_t)Color::White].pieceBitboards[(int)PieceType::Knight] & mask) pieceChar = "♞";
            else if (players[(uint8_t)Color::White].pieceBitboards[(int)PieceType::Bishop] & mask) pieceChar = "♝";
            else if (players[(uint8_t)Color::White].pieceBitboards[(int)PieceType::Queen] & mask) pieceChar = "♛";
            else if (players[(uint8_t)Color::White].pieceBitboards[(int)PieceType::King] & mask) pieceChar = "♚";

            cout << pieceChar << " ";
        }
        cout << endl;
    }
}

void Board::move(uint32_t move) {
    auto [piece, color, from, to] = Utils::parseMove(move);

    uint64_t fromMask = 1ULL << from;
    uint64_t toMask   = 1ULL << to;

    Player& player = players[color];

    player.pieceBitboards[piece] &= ~fromMask;
    player.pieceBitboards[piece] |= toMask;
}