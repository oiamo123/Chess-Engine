#include "./rules.h"
#include "../Utils/utils.h"

Rules::Rules(
    Player& white, 
    Player& black, 
    MoveGenerator& moveGenerator
) : white(white), black(black), moveGenerator(moveGenerator) {};

bool Rules::IsLegalMove(
    uint8_t piece,
    uint8_t color,
    uint8_t from, 
    uint8_t to 
) {
    // data parsing
    Player& friendlyPlayer = color == (uint8_t)Color::White ? white : black;
    Player& opposingPlayer = color == (uint8_t)Color::White ? black : white;
    uint64_t allPieces = friendlyPlayer.occupiedSquares | opposingPlayer.occupiedSquares;

    uint64_t toBitboard = (1ULL << to);
    uint64_t fromBitboard = (1ULL << from);
    uint64_t moves = 0ULL;

    // check from is friendly and to is not friendly
    if (!(fromBitboard & friendlyPlayer.occupiedSquares)) return false;
    if (toBitboard & friendlyPlayer.occupiedSquares) return false;

    // sliding pieces
    if (
        (PieceType)piece == PieceType::Queen ||
        (PieceType)piece == PieceType::Rook ||
        (PieceType)piece == PieceType::Bishop
    ) {
        // moves must contain to square and there can't be any pieces on the returned "between" ray
        moves |= moveGenerator.getBetweenMoves(from, to, piece);
        if (moves & allPieces) return false;
        return true;
    }

    // knight
    if (PieceType(piece) == PieceType::Knight) {
        // moves must contain to square
        moves |= moveGenerator.getKnightMoves(from);
        if (!(moves & toBitboard)) return false;
        return true;
    }

    // pawn
    if (PieceType(piece) == PieceType::Pawn) {
        auto [pushes, attacks] = moveGenerator.getPawnMoves(from, color);

        // handle pushes
        if (pushes && (pushes & toBitboard)) {
            // can't be any pieces on any of the push squares
            if (toBitboard & allPieces) return false;        
            
            // validate double push for white
            if (color == (uint8_t)Color::White && (fromBitboard & RANK_2) && (to == from + 16)) {
                if ((fromBitboard << 8) & allPieces) return false;
            }
            
            // validate double push for black
            if (color == (uint8_t)Color::Black && (fromBitboard & RANK_7) && (to == from - 16)) {
                if ((fromBitboard >> 8) & allPieces) return false;
            }

        // validate attacks
        } else if (attacks & toBitboard) {
            if (!(toBitboard & (opposingPlayer.occupiedSquares | opposingPlayer.enPassantSquare))) return false;
        }
        
        return true;
    }

    // king
    if (PieceType(piece) == PieceType::King) {
        // normal move
        moves = moveGenerator.getKingMoves(from);
        if (moves & toBitboard) return true;

        // if it's not a normal move, it's a castle. validate that the move the to square is on the right rank
        if (color == (uint8_t)Color::White && !(RANK_1 & toBitboard)) return false;
        if (color == (uint8_t)Color::Black && !(RANK_8 & toBitboard)) return false;

        auto [moves, castlingType] = moveGenerator.getCastlingMoves(to);
        if (!moves) return false;

        // ensure:
        // - player can castle king / queen side
        // - none of the squares are threatened
        // - no pieces in between
        if (castlingType == (uint8_t)CastlingType::Kingside && !friendlyPlayer.canCastleK) return false;
        if (castlingType == (uint8_t)CastlingType::Queenside && !friendlyPlayer.canCastleQ) return false;
        if (moves & allPieces) return false;
        if (moves & opposingPlayer.threats) return false;

        return true;
    }
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