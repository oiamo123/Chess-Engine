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
            if (!moves) return false;
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

            // pawn pushes
            if (pushes && (pushes & toBitboard)) {
                if (toBitboard & allPieces) return false;        
            
                // double pushes
                if (color == (uint8_t)Color::White && (fromBitboard & RANK_2) && (to == from + 16)) {
                    if ((fromBitboard << 8) & allPieces) return false;
                }
            
                if (color == (uint8_t)Color::Black && (fromBitboard & RANK_7) && (to == from - 16)) {
                    if ((fromBitboard >> 8) & allPieces) return false;
                }

            // pawn attacks
            } else if (attacks & toBitboard) {
                if (!(toBitboard & (opposingPlayer.occupiedSquares | opposingPlayer.enPassantSquare))) return false;
            }
        
            return true;
        
        // king
        case (uint8_t)PieceType::King:
            // normal move
            moves = MoveGenerator::kingTable[from];
            if (moves & toBitboard) return true;

            moves = MoveGenerator::castlingTable[to];
            if (!moves) return false;

            auto castlingType = (to == (uint8_t)Square::B1 || to == (uint8_t)Square::B7) ? 
                (uint8_t)CastlingType::Queenside : (uint8_t)CastlingType::Kingside;

            // ensure:
            // - player can castle king / queen side
            // - no pieces between
            if (castlingType == (uint8_t)CastlingType::Kingside && !friendlyPlayer.canCastleK) return false;
            if (castlingType == (uint8_t)CastlingType::Queenside && !friendlyPlayer.canCastleQ) return false;
            if (moves & allPieces) return false;

            return true;
    }

    return false;
}

bool Rules::isThreatened(uint8_t square, Player& friendly, Player& opposing) {
    uint64_t squareBitboard = (1ULL << square);

    // knight
    if (MoveGenerator::knightTable[square] & opposing.knights) return true;

    // king
    if (MoveGenerator::kingTable[square] & opposing.king) return true;

    // pawn
    if (MoveGenerator::pawnTable[friendly.color][1][square] & opposing.pawns) return true;

    // sliding pieces
    for (uint8_t i = (uint8_t)PieceIndex::B1; i <= (uint8_t)PieceIndex::Q; i++) {
        if (opposing.pieces[i] == NO_SQUARE) continue; 
        uint8_t pieceType = ((uint8_t)i - (uint8_t)PieceIndex::B1) >> 1;

        uint8_t pieceLocation = opposing.pieces[i];
        uint64_t ray = MoveGenerator::betweenTable[pieceType][square][pieceLocation];

        if (ray && !(ray & (friendly.occupiedSquares | opposing.occupiedSquares))) return true;
    }

    return false;
}

bool Rules::isInCheck(
    uint8_t piece,
    uint8_t square,
    Player& friendly,
    Player& opposing
) {
    // check if castling
    if (piece == (uint8_t)PieceType::King) {
        switch (square) {
             // white queenside
            case (uint8_t)Square::B2:
                if (isThreatened(friendly.pieces[(uint8_t)PieceIndex::K], friendly, opposing) ||
                    isThreatened((uint8_t)Square::C1, friendly, opposing) ||
                    isThreatened((uint8_t)Square::D1, friendly, opposing))
                    return true;
                break;

            // black queenside
            case (uint8_t)Square::B7: 
                if (isThreatened(friendly.pieces[(uint8_t)PieceIndex::K], friendly, opposing) ||
                    isThreatened((uint8_t)Square::C8, friendly, opposing))
                    return true;
                break;

            // white kingside
            case (uint8_t)Square::H2: 
                if (isThreatened(friendly.pieces[(uint8_t)PieceIndex::K], friendly, opposing) ||
                    isThreatened((uint8_t)Square::F1, friendly, opposing) ||
                    isThreatened((uint8_t)Square::G1, friendly, opposing))
                    return true;
                break;

            // black kingside
            case (uint8_t)Square::H7: 
                if (isThreatened(friendly.pieces[(uint8_t)PieceIndex::K], friendly, opposing) ||
                    isThreatened((uint8_t)Square::F8, friendly, opposing))
                    return true;
                break;
        }
    }

    // general
    return isThreatened(friendly.pieces[(uint8_t)PieceIndex::K], friendly, opposing);
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