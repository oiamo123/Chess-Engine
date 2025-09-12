#ifndef PAWN_H
#define PAWN_H
#include "../Piece/piece.h"
#include "../../Utils/global.h"

class Pawn : public Piece {
    public:
    Pawn(int8_t color, int16_t position)
        : Piece(static_cast<int8_t>(PieceType::Pawn), color, position) {}
    vector<int32_t> getMoves() override;
};

#endif