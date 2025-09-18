#ifndef QUEEN_H
#define QUEEN_H
#include "../Piece/piece.h"
#include "../../Utils/global.h"
using std::uint8_t;
using std::uint16_t;
using std::uint32_t;

class Queen : public Piece {
    public:
    Queen(uint8_t color, uint16_t position)
        : Piece(static_cast<uint8_t>(PieceType::Queen), color, position) {}
    vector<uint32_t> getMoves() override;
};

#endif