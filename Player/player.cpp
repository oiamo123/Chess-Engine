#include "player.h"
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
    pieceBitboards[(int)PieceType::Rook]   = rooks;
    pieceBitboards[(int)PieceType::Knight] = knights;
    pieceBitboards[(int)PieceType::Bishop] = bishops;
    pieceBitboards[(int)PieceType::Pawn]   = pawns;
    pieceBitboards[(int)PieceType::Queen]  = queen;
    pieceBitboards[(int)PieceType::King]   = king;
}

uint64_t Player::getAllPieces() {
    uint64_t all = 0ULL;
    for (int i = 0; i < (int)PieceType::Count; ++i) all |= pieceBitboards[i];
    return all;
}

uint64_t& Player::operator[](PieceType type) {
    return pieceBitboards[(int)type];
}
