#ifndef GLOBAL_H
#define GLOBAL_H

#include <cstdint>
#include <array>
#include <vector>

using std::vector;
using std::array;
using std::uint8_t;
using std::uint64_t;

constexpr uint8_t NO_SQUARE = 64;
constexpr uint8_t NO_PIECE = 16;

constexpr uint64_t MASK_8 = 0xFF;
constexpr uint64_t MASK_16 = 0xFFFF;
constexpr uint64_t MASK_32 = 0xFFFFFFFF;
constexpr uint64_t MASK_64 = 0xFFFFFFFFFFFFFFFF;

constexpr uint64_t FILE_A = 0x0101010101010101;
constexpr uint64_t FILE_B = FILE_A << 1;
constexpr uint64_t FILE_C = FILE_A << 2;
constexpr uint64_t FILE_D = FILE_A << 3;
constexpr uint64_t FILE_E = FILE_A << 4;
constexpr uint64_t FILE_F = FILE_A << 5;
constexpr uint64_t FILE_G = FILE_A << 6;
constexpr uint64_t FILE_H = FILE_A << 7;

constexpr uint64_t RANK_1 = 0x00000000000000FF;
constexpr uint64_t RANK_2 = RANK_1 << (8 * 1);
constexpr uint64_t RANK_3 = RANK_1 << (8 * 2);
constexpr uint64_t RANK_4 = RANK_1 << (8 * 3);
constexpr uint64_t RANK_5 = RANK_1 << (8 * 4);
constexpr uint64_t RANK_6 = RANK_1 << (8 * 5);
constexpr uint64_t RANK_7 = RANK_1 << (8 * 6);
constexpr uint64_t RANK_8 = RANK_1 << (8 * 7);

enum class PieceIndex : uint8_t {
    P1 = 0,
    P2,
    P3,
    P4,   
    P5,
    P6,
    P7,
    P8,
    N1,
    N2,
    B1,
    B2,
    R1,
    R2,
    Q,
    K   
};

enum class PieceType : uint8_t {
    Pawn = 0,
    Knight,
    Bishop,
    Rook,
    Queen,
    King,
    Count
};

enum class Color : uint8_t {
    White,
    Black
};

enum class Square : uint8_t {
    A1 = 0, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8
};

enum class Direction : uint8_t {
    N,
    NE,
    E,
    SE,
    S,
    SW,
    W,
    NW
};

enum class CastlingType {
    Kingside = 0,
    Queenside
};

struct FenParams {
    array<vector<uint8_t>, 6> blackPieces;
    array<vector<uint8_t>, 6> whitePieces;
    array<array<bool, 2>, 2> castlingRights;
    uint8_t turn;
    uint8_t enPassantSquare;
    uint8_t halfMoves;
    uint8_t fullMoves;
};

#endif