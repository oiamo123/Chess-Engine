#include "./rules.h"
#include "../Utils/utils.h"

bool Rules::isLegalMove(const std::array<std::unique_ptr<Player>, 2>& players, const int32_t move) {
    auto [color, piece, from, to] = Utils::parseMove(move);
    if (Rules::isInCheck(players, color) || !Rules::isMovingOwnPiece(players, move)) {
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
            return true;
        }

        // Captures
        if (
            (to == from + 7 * direction || to == from + 9 * direction) &&
            (toBitboard & (color == (int8_t)Color::White ? blackPieces : whitePieces))
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

    return true;
}

bool Rules::isInCheck(const std::array<std::unique_ptr<Player>, 2>& players, const int playerColor) {
    return true;
}

bool Rules::isInCheckmate(const std::array<std::unique_ptr<Player>, 2>& players, const int playerColor) {
    return true;
}

bool Rules::isInStalemate(const std::array<std::unique_ptr<Player>, 2>& players, const int playerColor) {
    return true;
}

bool Rules::isDraw(const std::array<std::unique_ptr<Player>, 2>& players) {
    return true;
}

bool Rules::isMovingOwnPiece(const std::array<std::unique_ptr<Player>, 2>& players, const int32_t move) {
    auto [color, piece, from, to] = Utils::parseMove(move);
    const int white = (int)Color::White;
    const int black = (int)Color::Black;

    const uint64_t fromBitboard = Utils::indexToBitboard(from);

    if (color == (int8_t)Color::White) {
        return players[white]->pieceBitboards[piece] & fromBitboard;
    } else {
        return players[black]->pieceBitboards[piece] & fromBitboard;
    }
}