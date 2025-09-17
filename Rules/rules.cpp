#include "./rules.h"
#include "../Utils/utils.h"
#include "../Board/board.h"
#include "./move_generation.h"

using std::unique_ptr;

Rules::Rules(Board* board) {
    this->board = board;
    this->knightmoves = MoveGenerator::generateKnightTable();
    this->bishopmoves = MoveGenerator::generateBishopTable();
    this->rookmoves = MoveGenerator::generateRookTable();
    this->queenmoves = MoveGenerator::generateQueenTable(this->bishopmoves, this->rookmoves);
}

bool Rules::isLegalMove(const int32_t move) {
    auto& players = board->players;
    auto [color, piece, from, to] = Utils::parseMove(move);
    if (!Rules::isMovingOwnPiece(move)) {
        return false;
    }

    // Helper variables
    const int white = (int)Color::White;
    const int black = (int)Color::Black;
    const bool isWhite = (color == (int8_t)Color::White);

    const uint64_t allPieces = players[white]->getAllPieces() | players[black]->getAllPieces();
    const uint64_t whitePieces = players[white]->getAllPieces();
    const uint64_t blackPieces = players[black]->getAllPieces();
    const uint64_t friendlyPieces = isWhite ? whitePieces : blackPieces;
    const uint64_t enemyPieces = isWhite ? blackPieces : whitePieces;

    const uint64_t toBitboard = Utils::indexToBitboard(to);
    const uint64_t fromBitboard = Utils::indexToBitboard(from);

    // Rules for pawn
    if (piece == (int8_t)PieceType::Pawn) {
        const int8_t forward = isWhite ? 1 : -1;
        const int startRank = isWhite ? RANK_2 : RANK_7;
        
        auto shiftRank = [](uint64_t bb, int8_t rankShift) -> uint64_t {
            return rankShift > 0 ? bb << (8 * rankShift) : bb >> (8 * -rankShift);
        };

        // Single push
        if (to == from + 8 * forward && !(allPieces & toBitboard))
            return true;

        // Double push
        if (to == from + 16 * forward && (from / 8 == startRank) &&
            !(allPieces & toBitboard) &&
            !(allPieces & shiftRank(fromBitboard, forward))) 
        {
            // Set en passant target
            players[isWhite ? black : white]->enPassantTarget = shiftRank(fromBitboard, forward);
            return true;
        }

        // Captures (including en passant)
        int fileDiff = abs((to % 8) - (from % 8));
        if ((to == from + 7 * forward || to == from + 9 * forward) && fileDiff == 1 &&
            ((toBitboard & enemyPieces) ||
            toBitboard == players[isWhite ? black : white]->enPassantTarget))
        {
            return true;
        }

        return false;
    }

    // Rules for knight
    if (piece == (int8_t)PieceType::Knight) {
        if ((knightmoves.at(fromBitboard) & toBitboard) && !(toBitboard & friendlyPieces)) {
            return true;
        }
    }
    
    // Rules for bishop
    if (piece == (int8_t)PieceType::Bishop) {
    }
    
    // Rules for rook
    if (piece == (int8_t)PieceType::Rook) {
    }
    
    // Rules for queen
    if (piece == (int8_t)PieceType::Queen) {
    }
    
    // Rules for king
    if (piece == (int8_t)PieceType::King) {
    }

    // Make move, check if king is in check, undo move

    return true;
}

bool Rules::isInCheck() {
    return true;
}

bool Rules::isInCheckmate() {
    return true;
}

bool Rules::isInStalemate() {
    return true;
}

bool Rules::isDraw() {
    return true;
}

bool Rules::isMovingOwnPiece(const int32_t move) {
    auto [color, piece, from, to] = Utils::parseMove(move);
    const int white = (int)Color::White;
    const int black = (int)Color::Black;

    const uint64_t fromBitboard = Utils::indexToBitboard(from);

    if (color == (int8_t)Color::White) {
        return board->players[white]->pieceBitboards[piece] & fromBitboard;
    } else {
        return board->players[black]->pieceBitboards[piece] & fromBitboard;
    }
}

map<uint64_t, uint64_t> Rules::generateKnightTable() {
}