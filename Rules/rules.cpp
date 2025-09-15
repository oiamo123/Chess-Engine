#include "./rules.h"
#include "../Utils/utils.h"
#include "../Board/board.h"

using std::unique_ptr;

Rules::Rules(Board* board) {
    this->board = board;
}

bool Rules::isLegalMove(const int32_t move) {
    auto& players = board->players;
    auto [color, piece, from, to] = Utils::parseMove(move);
    if (!Rules::isMovingOwnPiece(move)) {
        return false;
    }

    const int white = (int)Color::White;
    const int black = (int)Color::Black;
    
    const uint64_t allPieces = players[white]->getAllPieces() | players[black]->getAllPieces();
    const uint64_t whitePieces = players[white]->getAllPieces();
    const uint64_t blackPieces = players[black]->getAllPieces();

    const uint64_t toBitboard = Utils::indexToBitboard(to);
    const uint64_t fromBitboard = Utils::indexToBitboard(from);

    // Rules for pawn
    if (piece == (int8_t)PieceType::Pawn) {
        int8_t direction = (color == (int8_t)Color::White) ? 1 : -1;
        int startRank = (color == (int8_t)Color::White) ? RANK_2 : RANK_7;

        // Forward 1
        if (to == from + 8 * direction && !(allPieces & toBitboard)) {
            return true;
        }

        // Forward 2 (from starting rank)
        if (
            to == from + 16 * direction && (from / 8 == startRank) && 
            !(allPieces & toBitboard) && !(allPieces & (fromBitboard << (8 * direction)))
        ) {
            // Set en passant target
            players[(color == (int8_t)Color::White ? black : white)]->enPassantTarget = fromBitboard << (8 * direction);
            return true;
        }

        // Captures / enPassant
        if (
            (to == from + 7 * direction || to == from + 9 * direction) &&
            ((toBitboard & (color == (int8_t)Color::White ? blackPieces : whitePieces)) ||
            toBitboard == players[(color == (int8_t)Color::White ? black : white)]->enPassantTarget)
        ) {
            return true;
        }

        return false;
    }

    // Rules for knight
    if (piece == (int8_t)PieceType::Knight) {
        
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