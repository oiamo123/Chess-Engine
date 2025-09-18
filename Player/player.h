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
    uint64_t enPassantTarget;
    uint64_t attackedSquares;
    array<uint64_t, (uint8_t)PieceType::Count> pieceBitboards;

    uint64_t getAllPieces();
    uint64_t getAttackedSquares();
    void setPosition(
        uint8_t color,
        uint64_t rooks,
        uint64_t knights,
        uint64_t bishops,
        uint64_t pawns,
        uint64_t queen,
        uint64_t king
    );

    void move(uint32_t move);
    uint64_t& operator[](PieceType type);
};

#endif
