#include "player.h"
#include "../Utils/utils.h"
#include "../Utils/global.h"
using std::uint8_t;
using std::uint64_t;

void Player::setPosition(
        uint8_t color,
        uint64_t rooks,
        uint64_t knights,
        uint64_t bishops,
        uint64_t pawns,
        uint64_t queen,
        uint64_t king
) {
    this->color = color;
    pieceBitboards.fill(0ULL);
    pieceBitboards[(int)PieceType::Rook] = rooks;
    pieceBitboards[(int)PieceType::Knight] = knights;
    pieceBitboards[(int)PieceType::Bishop] = bishops;
    pieceBitboards[(int)PieceType::Pawn] = pawns;
    pieceBitboards[(int)PieceType::Queen] = queen;
    pieceBitboards[(int)PieceType::King] = king;
}

void move(uint8_t from, uint8_t to, uint8_t piece) {
    /*
    1. Get piece num -> slidingPieces[from]
    2. Set slidingpieces[pieceNum] -> to -> IsInCheck can just loop over, n worse case = 5
    3. Update appropriate bitboard
    */
    PieceType p = PieceType(piece);
    if (p == PieceType::Queen || p == PieceType::Rook || p == PieceType::Bishop) {
        uint8_t pieceNum = pieceLookup[from];
        pieceLookup[from] = -1;
        pieceLookup[to] = pieceNum;

        slidingPieces[pieceNum] = to;
    }
}

uint64_t& Player::operator[](PieceType type) {
    return pieceBitboards[(int)type];
}
