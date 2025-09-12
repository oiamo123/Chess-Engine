#ifndef ROOK_H
#define ROOK_H
#include "../Piece/piece.h"
#include "../../Utils/global.h"

class Rook : public Piece {
    public:
    Rook(int8_t color, int16_t position)
        : Piece(static_cast<int8_t>(PieceType::Rook), color, position) {}
    vector<int32_t> getMoves() override;
};

#endif