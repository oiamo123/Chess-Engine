#ifndef QUEEN_H
#define QUEEN_H
#include "../Piece/piece.h"
#include "../../Utils/global.h"

class Queen : public Piece {
    public:
    Queen(int8_t color, int16_t position)
        : Piece(static_cast<int8_t>(PieceType::Queen), color, position) {}
    vector<int32_t> getMoves() override;
};

#endif