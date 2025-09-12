#ifndef KNIGHT_H
#define KNIGHT_H
#include "../Piece/piece.h"
#include "../../Utils/global.h"

class Knight : public Piece {
    public:
    Knight(int8_t color, int16_t position)
        : Piece(static_cast<int8_t>(PieceType::Knight), color, position) {}
    vector<int32_t> getMoves() override;
};

#endif