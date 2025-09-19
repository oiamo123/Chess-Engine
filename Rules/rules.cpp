#include "./rules.h"
#include "../Utils/utils.h"
#include "../Board/board.h"
#include "./MoveGenerator/move_generator.h"
#include "./RayGenerator/ray_generator.h"

using std::uint8_t;
using std::uint16_t;
using std::uint64_t;
using std::array;

Rules::Rules(Board* board) : board(board), moveGenerator() {}

bool Rules::isLegalMove(const uint32_t move) {
    array<Player, 2>& players = board->players;
    auto [piece, color, from, to] = Utils::parseMove(move);
    
    if (!Rules::isMovingOwnPiece(move)) {
        return false;
    }

    // Helper variables
    const uint8_t white = (int)Color::White;
    const uint8_t black = (int)Color::Black;
    const bool isWhite = (color == (uint8_t)Color::White);

    const uint64_t allPieces = players[white].getAllPieces() | players[black].getAllPieces();
    const uint64_t whitePieces = players[white].getAllPieces();
    const uint64_t blackPieces = players[black].getAllPieces();
    const uint64_t friendlyPieces = isWhite ? whitePieces : blackPieces;
    const uint64_t enemyPieces = isWhite ? blackPieces : whitePieces;

    const uint64_t toBitboard = Utils::indexToBitboard(to);
    const uint64_t fromBitboard = Utils::indexToBitboard(from);

    // Rules for pawn
    if (piece == (uint8_t)PieceType::Pawn) {
        const uint8_t forward = isWhite ? 1 : -1;
        const uint64_t startRank = isWhite ? RANK_2 : RANK_7;
        
        auto shiftRank = [](uint64_t bb, uint8_t rankShift) -> uint64_t {
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
            players[isWhite ? black : white].enPassantTarget = shiftRank(fromBitboard, forward);
            return true;
        }

        // Captures (including en passant)
        int fileDiff = abs((to % 8) - (from % 8));
        if ((to == from + 7 * forward || to == from + 9 * forward) && fileDiff == 1 &&
            ((toBitboard & enemyPieces) ||
            toBitboard == players[isWhite ? black : white].enPassantTarget))
        {
            return true;
        }

        return false;
    }

    // Rules for knight
    if (piece == (uint8_t)PieceType::Knight) {
        if ((getMoves(move) & toBitboard) && !(toBitboard & friendlyPieces)) {
            return true;
        }
    }
    
    // Rules for king
    if (piece == (uint8_t)PieceType::King) {
    }


    // Otherwise it's a sliding piece and it either can or cannot move there. We just have to check if it puts the king in check
    getMoves(move) & toBitboard;

    return ;
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

bool Rules::isMovingOwnPiece(const uint32_t move) {
    auto [piece, color, from, to] = Utils::parseMove(move);
    const int white = (uint8_t)Color::White;
    const int black = (uint8_t)Color::Black;

    const uint64_t fromBitboard = Utils::indexToBitboard(from);

    if (color == (uint8_t)Color::White) {
        return board->players[white].pieceBitboards[piece] & fromBitboard;
    } else {
        return board->players[black].pieceBitboards[piece] & fromBitboard;
    }
}

uint64_t Rules::getMoves(const uint32_t move) {
    auto [piece, color, from, to] = Utils::parseMove(move);
    uint8_t opponentColor = color == (uint8_t)Color::White ? (uint8_t)Color::White : (uint8_t)Color::Black;
    uint64_t opponentPieces = board->players[opponentColor].getAllPieces();
    uint64_t friendlyPieces = board->players[color].getAllPieces();

    switch (piece) {
        case (uint8_t)PieceType::Knight: 
            return moveGenerator.generateKnightMoves(from);
        case (uint8_t)PieceType::Bishop: 
            return moveGenerator.generateBishopMoves(from, opponentPieces, friendlyPieces);
        case (uint8_t)PieceType::Rook: 
            return moveGenerator.generateRookMoves(from, opponentPieces, friendlyPieces);
        case (uint8_t)PieceType::Queen: 
            return moveGenerator.generateQueenMoves(from, opponentPieces, friendlyPieces);
        case (uint8_t)PieceType::King: 
            return moveGenerator.generateKingMoves(from, opponentPieces, friendlyPieces);
        default: 
            return 0ULL;
    }
}