#include "./rules.h"
#include "../Utils/utils.h"

Rules::Rules(
    Player& white, 
    Player& black
) : white(white), black(black) {};

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

    switch (piece) {
        // sliding pieces
        case (uint8_t)PieceType::Bishop:
        case (uint8_t)PieceType::Rook:
        case (uint8_t)PieceType::Queen:
            moves |= MoveGenerator::betweenTable[piece][from][to];
            if (moves & allPieces) return false;
            return true;

        // knight
        case (uint8_t)PieceType::Knight:
            moves |= MoveGenerator::knightTable[from];
            if (!(moves & toBitboard)) return false;
            return true;

        // pawn
        case (uint8_t)PieceType::Pawn:
            auto pushes = MoveGenerator::pawnTable[color][0][from];
            auto attacks = MoveGenerator::pawnTable[color][1][from];

            // handle pushes
            if (pushes && (pushes & toBitboard)) {
                if (toBitboard & allPieces) return false;        
            
                // validate double pushes
                if (color == (uint8_t)Color::White && (fromBitboard & RANK_2) && (to == from + 16)) {
                    if ((fromBitboard << 8) & allPieces) return false;
                }
            
                if (color == (uint8_t)Color::Black && (fromBitboard & RANK_7) && (to == from - 16)) {
                    if ((fromBitboard >> 8) & allPieces) return false;
                }

            // handle attacks
            } else if (attacks & toBitboard) {
                if (!(toBitboard & (opposingPlayer.occupiedSquares | opposingPlayer.enPassantSquare))) return false;
            }
        
            return true;
        
        // king
        case (uint8_t)PieceType::King:
            // normal move
            moves = MoveGenerator::kingTable[from];
            if (moves & toBitboard) return true;

            // castling
            if (color == (uint8_t)Color::White && !(RANK_1 & toBitboard)) return false;
            if (color == (uint8_t)Color::Black && !(RANK_8 & toBitboard)) return false;

            auto moves = MoveGenerator::castlingTable[to];
            auto castlingType = to == (2 || 58) ? (uint8_t)CastlingType::Kingside : (uint8_t)CastlingType::Queenside;

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

bool Rules::isInCheck(
    uint8_t piece,
    uint8_t from, 
    uint8_t to, 
    Player friendly, 
    Player opposing
) {
    // king is moving
    if (piece == (uint8_t)PieceType::King) {


    // any other piece is moving
    } else {

    }
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