#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <array>
#include <cstdint>
#include "../Utils/global.h"

using std::array;
using std::vector;
using std::uint8_t;
using std::uint32_t;
using std::uint64_t;

class Player {
    public:
    Player() = default;
    uint64_t pawns;
    uint64_t knights;
    uint64_t knights;
    uint64_t bishops;
    uint64_t rooks;
    uint64_t queen;
    uint64_t king;
    
    uint8_t color;
    uint64_t occupiedSquares;
    uint64_t enPassantSquare;
    
    bool canCastleK;
    bool canCastleQ;

    Player(
        uint8_t color,
        vector<uint8_t> pawns,
        vector<uint8_t> knights,
        vector<uint8_t> bishops,
        vector<uint8_t> rooks,
        uint8_t queen,
        uint8_t king
    );

    array<uint8_t, 16> pieces;
    array<uint8_t, 64> lookup;
    array<uint8_t, 6> slidingPieces;

    private:
    void setPosition(
        vector<uint8_t> pawns,
        vector<uint8_t> knights,
        vector<uint8_t> bishops,
        vector<uint8_t> rooks,
        uint8_t queen,
        uint8_t king
    );
    void setPiece(uint8_t index, uint8_t pieceIndex);
};

#endif
