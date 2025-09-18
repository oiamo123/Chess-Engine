#ifndef KNIGHT_H
#define KNIGHT_H
#include "../Piece/piece.h"
#include "../../Utils/global.h"
using std::uint8_t;
using std::uint32_t;
using std::uint16_t;

class Knight : public Piece {
    public:
    Knight(uint8_t color, uint16_t position)
        : Piece(static_cast<uint8_t>(PieceType::Knight), color, position) {}
    vector<uint32_t> getMoves() override;
};

#endif