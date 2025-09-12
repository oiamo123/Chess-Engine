#ifndef PLAYER_H
#define PLAYER_H

#include <array>
#include <cstdint>
#include "../Utils/global.h"

class Player {
public:
    int8_t color;
    std::array<uint64_t, (int)PieceType::Count> pieceBitboards;

    Player(
        int8_t color,
        uint64_t rooks,
        uint64_t knights,
        uint64_t bishops,
        uint64_t pawns,
        uint64_t queen,
        uint64_t king
    );

    uint64_t getAllPieces() const;
    uint64_t& operator[](PieceType type);
};

#endif
