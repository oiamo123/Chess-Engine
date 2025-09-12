#ifndef GLOBAL_H
#define GLOBAL_H
#include <cstdint>

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

enum class PieceType : int8_t {
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King,
    Count
};

enum class Color : int8_t {
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

#endif