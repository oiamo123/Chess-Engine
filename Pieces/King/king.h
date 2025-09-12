#ifndef KING_H
#define KING_H
#include "../Piece/piece.h"
#include "../../Utils/global.h"

class King : public Piece {
    public:
    King(int8_t color, int16_t position)
        : Piece(static_cast<int8_t>(PieceType::King), color, position) {}
    vector<int32_t> getMoves() override;
};

#endif