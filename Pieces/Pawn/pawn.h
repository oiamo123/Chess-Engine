#ifndef PAWN_H
#define PAWN_H
#include "../Piece/piece.h"
#include "../../Utils/global.h"
using std::uint8_t;
using std::uint32_t;
using std::uint16_t;

class Pawn : public Piece {
    public:
    Pawn(uint8_t color, uint16_t position)
        : Piece(static_cast<uint8_t>(PieceType::Pawn), color, position) {}
    vector<uint32_t> getMoves() override;
};

#endif