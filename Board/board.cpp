#include "./board.h"
#include "../Utils/utils.h"
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

Board::Board(const string fen) : moveGenerator(), players(), rules(this->players[0], this->players[1], this->moveGenerator) {
    create(fen);
}

void Board::create(const string fen) {
    InitParams initParams = InitParams();
    Utils::parseFen(fen, initParams);
    
    createPlayers(initParams.whitePieces, initParams.blackPieces);
    setPinned();
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

void Board::createPlayers(
    array<vector<uint8_t>, 6> whitePieces,
    array<vector<uint8_t>, 6> blackPieces
) {
    if (whitePieces.size() == 0) {
        players[(uint8_t)Color::White] = Player(
            (uint8_t)Color::White, 
            { 8, 9, 10, 11, 12, 13, 14, 15 }, 
            { 2, 5 }, 
            { 1, 6 }, 
            { 0, 7 }, 
            { 3 }, 
            { 4 } 
        );

        players[(uint8_t)Color::Black] = Player(
            (uint8_t)Color::Black, 
            { 48, 49, 50, 51, 52, 53, 54, 55 }, 
            { 58, 61 }, 
            { 57, 62 }, 
            { 56, 63 }, 
            { 59 }, 
            { 60 }  
        );

    } else {
        players[(uint8_t)Color::White] = Player(
            (uint8_t)Color::White, 
            whitePieces[(uint8_t)PieceType::Pawn], 
            whitePieces[(uint8_t)PieceType::Knight], 
            whitePieces[(uint8_t)PieceType::Bishop], 
            whitePieces[(uint8_t)PieceType::Rook], 
            whitePieces[(uint8_t)PieceType::Queen][0], 
            whitePieces[(uint8_t)PieceType::King][0]
        );

        players[(uint8_t)Color::Black] = Player(
            (uint8_t)Color::Black, 
            blackPieces[(uint8_t)PieceType::Pawn], 
            blackPieces[(uint8_t)PieceType::Knight], 
            blackPieces[(uint8_t)PieceType::Bishop], 
            blackPieces[(uint8_t)PieceType::Rook], 
            blackPieces[(uint8_t)PieceType::Queen][0], 
            blackPieces[(uint8_t)PieceType::King][0]
        );
    }
}

void Board::setPinned() {

}

void Board::move(uint32_t move) {
    auto [piece, color, from, to] = Utils::parseMove(move);

    uint64_t fromMask = 1ULL << from;
    uint64_t toMask   = 1ULL << to;

    Player& player = players[color];

    player.pieceBitboards[piece] &= ~fromMask;
    player.pieceBitboards[piece] |= toMask;
}