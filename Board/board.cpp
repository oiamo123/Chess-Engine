#include "./board.h"
#include "../Utils/utils.h"
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

Board::Board(
    const string fen
) : players(), rules(this->players[0], this->players[1]) {
    create(fen);
}

// creates the board
void Board::create(const string fen) {    
    FenParams fenParams;
    Utils::parseFen(fen, fenParams);
    createPlayers(fenParams.whitePieces, fenParams.blackPieces);
    display();
}

// displays the board
void Board::display() {
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            int square = rank * 8 + file;
            string pieceChar = ".";

            Player& black = players[(uint8_t)Color::Black];
            Player& white = players[(uint8_t)Color::White];

            uint8_t blackPieceIndex = black.lookup[square];
            uint8_t whitePieceIndex = white.lookup[square];

            if (blackPieceIndex != NO_PIECE) {
                if (blackPieceIndex <= (uint8_t)PieceIndex::P8) pieceChar = "♙";
                else if (blackPieceIndex <= (uint8_t)PieceIndex::N2) pieceChar = "♘";
                else if (blackPieceIndex <= (uint8_t)PieceIndex::B2) pieceChar = "♗";
                else if (blackPieceIndex <= (uint8_t)PieceIndex::R2) pieceChar = "♖";
                else if (blackPieceIndex == (uint8_t)PieceIndex::Q) pieceChar = "♕";
                else if (blackPieceIndex == (uint8_t)PieceIndex::K) pieceChar = "♔";
            }

            else if (whitePieceIndex != NO_PIECE) {
                if (whitePieceIndex <= (uint8_t)PieceIndex::P8) pieceChar = "♟";
                else if (whitePieceIndex <= (uint8_t)PieceIndex::N2) pieceChar = "♜";
                else if (whitePieceIndex <= (uint8_t)PieceIndex::B2) pieceChar = "♞";
                else if (whitePieceIndex <= (uint8_t)PieceIndex::R2) pieceChar = "♝";
                else if (whitePieceIndex == (uint8_t)PieceIndex::Q) pieceChar = "♛";
                else if (whitePieceIndex == (uint8_t)PieceIndex::K) pieceChar = "♚";
            }

            cout << pieceChar << " ";
        }
        cout << endl;
    }
}

// creates the players
void Board::createPlayers(
    array<vector<uint8_t>, 6> whitePieces,
    array<vector<uint8_t>, 6> blackPieces
) {
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

void Board::move(uint32_t move) {
    auto [piece, color, from, to] = Utils::parseMove(move);

    // check if the move is legal
    if (!rules.IsLegalMove(piece, color, from, to)) return;

    // if it is legal, make the move
    Player& friendly = color == (uint8_t)Color::White ? players[(uint8_t)Color::White] : players[(uint8_t)Color::Black];
    Player& opponent = color == (uint8_t)Color::White ? players[(uint8_t)Color::Black] : players[(uint8_t)Color::White];
    uint64_t friendlyKingPos = friendly.lookup[(uint8_t)PieceIndex::K];
    uint64_t opponentKingPos = opponent.lookup[(uint8_t)PieceIndex::K];

    MoveParams moveParams = MoveParams(
        friendly,
        opponent,
        friendlyKingPos,
        opponentKingPos,
        piece,
        color,
        from,
        to
    );

    if (abs((int)to - (int)from) == 2) {
        processCastle(moveParams);
    } else {
        processMove(moveParams);
    }
}

void Board::processCastle(const MoveParams& moveParams) {
    
}

void Board::processMove(const MoveParams& moveParams) {
    
}
