#include "./rules.h"
#include "../Utils/utils.h"

Rules::Rules(
    Player& white, 
    Player& black, 
    MoveGenerator& moveGenerator
) : white(white), black(black), moveGenerator(moveGenerator) {};

bool Rules::IsLegalMove(uint32_t move) {
    auto [piece, color, from, to] = Utils::parseMove(move);
    Player curPlayer = color == (uint8_t)Color::White ? white : black;
    Player opposingPlayer = color == (uint8_t) Color::White ? black : white;
    uint64_t allPieces = curPlayer.occupiedSquares | opposingPlayer.occupiedSquares;
    uint64_t moves = 0ULL;

    if (to & curPlayer.occupiedSquares) return false;
    if (!(from & curPlayer.occupiedSquares)) return false;

    if (
        (PieceType)piece == PieceType::Queen ||
        (PieceType)piece == PieceType::Rook ||
        (PieceType)piece == PieceType::Bishop
    ) {
        moves |= moveGenerator.getBetweenMove(from, to, piece);
        if (!moves) return false;
        if (moves & allPieces) return false;
        return true;
    }

    if (PieceType(piece) == PieceType::Knight) {
        moves |= moveGenerator.getKnightMove(from);
        if (!(moves & to)) return false;
    }

    if (PieceType(piece) == PieceType::Pawn) {
        auto [pushes, attacks] = moveGenerator.getPawnMove(from, color);
        if ((to & attacks) && !(to & opposingPlayer.occupiedSquares)) return false;
        if (from & RANK_2 && (from << 8) & allPieces) return false;
        if (from & RANK_7 && (from >> 8) & allPieces) return false;
    }

    return true;
}

bool Rules::isInCheck(uint8_t from, uint8_t to, Player cur, Player opposing) {
    uint64_t allPieces = cur.occupiedSquares | opposing.occupiedSquares;

    

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