#ifndef PLAYER_H
#define PLAYER_H

#include <array>
#include <cstdint>
#include "../Utils/global.h"

using std::uint8_t;
using std::uint32_t;
using std::uint64_t;
using std::array;

class Player {
    public:
    uint8_t color;
    uint64_t occupiedSquares;
    array<uint64_t, 6> pieceBitboards;
    array<uint8_t, 5> slidingPieceTable;
    array<uint8_t, 5> pieceCount;

    void setPosition(
        uint8_t color,
        uint64_t rooks,
        uint64_t knights,
        uint64_t bishops,
        uint64_t pawns,
        uint64_t queen,
        uint64_t king
    );
    
    void move(uint8_t from, uint8_t to, uint8_t piece);

    uint64_t& operator[](PieceType type);
};

#endif
