#ifndef BISHOP_H
#define BISHOP_H
#include "../Piece/piece.h"
#include "../../Utils/global.h"

class Bishop : public Piece {
    public:
    Bishop(int8_t color, int16_t position)
        : Piece(static_cast<int8_t>(PieceType::Bishop), color, position) {}
    vector<int32_t> getMoves() override;
};

#endif