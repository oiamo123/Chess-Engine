#ifndef GLOBAL_H
#define GLOBAL_H
#include <cstdint>

constexpr uint64_t MASK_8 = 0xFF;
constexpr uint64_t MASK_16 = 0xFFFF;
constexpr uint64_t MASK_32 = 0xFFFFFFFF;
constexpr uint64_t MASK_64 = 0xFFFFFFFFFFFFFFFF;

enum class PieceType {
    Pawn = 1,
    Knight,
    Bishop,
    Rook,
    Queen,
    King
};

enum class Color {
    White = 1,
    Black
};

#endif