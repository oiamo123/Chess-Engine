#ifndef MOVE_GENERATOR_TPP
#define MOVE_GENERATOR_TPP

#include <iostream>
#include "./move_generator.h"
#include "../../Utils/utils.h"

template<>
__attribute__((always_inline)) inline uint64_t MoveGenerator::getLegalMovesForRay<Direction::N>(
    uint8_t from,
    uint64_t opponentPieces,
    uint64_t friendlyPieces
) {
    const uint64_t ray = raysN[from];
    const uint64_t blockers = ray & (opponentPieces | friendlyPieces);

    if (!blockers) {
        return ray;
    }

    const uint64_t nearest = getRightMostBit(blockers);
    uint64_t moves = ray & ((nearest - 1) | nearest);

    if (nearest & friendlyPieces) {
        moves &= ~nearest;
    }

    return moves;
}

template<>
__attribute__((always_inline)) inline uint64_t MoveGenerator::getLegalMovesForRay<Direction::NE>(
    uint8_t from,
    uint64_t opponentPieces,
    uint64_t friendlyPieces
) {
    const uint64_t ray = raysNE[from];
    const uint64_t blockers = ray & (opponentPieces | friendlyPieces);

    if (!blockers) {
        return ray;
    }

    const uint64_t nearest = getRightMostBit(blockers);
    uint64_t moves = ray & ((nearest - 1) | nearest);

    if (nearest & friendlyPieces) {
        moves &= ~nearest;
    }

    return moves;
}

template<>
__attribute__((always_inline)) inline uint64_t MoveGenerator::getLegalMovesForRay<Direction::E>(
    uint8_t from,
    uint64_t opponentPieces,
    uint64_t friendlyPieces
) {
    const uint64_t ray = raysE[from];
    const uint64_t blockers = ray & (opponentPieces | friendlyPieces);

    if (!blockers) {
        return ray;
    }

    const uint64_t nearest = getLeftMostBit(blockers);
    uint64_t moves = ray & ((nearest - 1) | nearest);

    if (nearest & friendlyPieces) {
        moves &= ~nearest;
    }

    return moves;
}

template<>
__attribute__((always_inline)) inline uint64_t MoveGenerator::getLegalMovesForRay<Direction::SE>(
    uint8_t from,
    uint64_t opponentPieces,
    uint64_t friendlyPieces
) {
    const uint64_t ray = raysSE[from];
    const uint64_t blockers = ray & (opponentPieces | friendlyPieces);

    if (!blockers) {
        return ray;
    }

    const uint64_t nearest = getLeftMostBit(blockers);
    uint64_t moves = ray & ~(nearest - 1);

    if (nearest & friendlyPieces) {
        moves &= ~nearest;
    }

    return moves;
}

template<>
__attribute__((always_inline)) inline uint64_t MoveGenerator::getLegalMovesForRay<Direction::S>(
    uint8_t from,
    uint64_t opponentPieces,
    uint64_t friendlyPieces
) {
    const uint64_t ray = raysS[from];
    const uint64_t blockers = ray & (opponentPieces | friendlyPieces);

    if (!blockers) {
        return ray;
    }

    const uint64_t nearest = getLeftMostBit(blockers);
    uint64_t moves = ray & ~(nearest - 1);

    if (nearest & friendlyPieces) {
        moves &= ~nearest;
    }

    return moves;
}

template<>
__attribute__((always_inline)) inline uint64_t MoveGenerator::getLegalMovesForRay<Direction::SW>(
    uint8_t from,
    uint64_t opponentPieces,
    uint64_t friendlyPieces
) {
    const uint64_t ray = raysSW[from];
    const uint64_t blockers = ray & (opponentPieces | friendlyPieces);

    if (!blockers) {
        return ray;
    }

    const uint64_t nearest = getRightMostBit(blockers);
    uint64_t moves = ray & ~(nearest - 1);

    if (nearest & friendlyPieces) {
        moves &= ~nearest;
    }

    return moves;
}

template<>
__attribute__((always_inline)) inline uint64_t MoveGenerator::getLegalMovesForRay<Direction::W>(
    uint8_t from,
    uint64_t opponentPieces,
    uint64_t friendlyPieces
) {
    const uint64_t ray = raysW[from];
    const uint64_t blockers = ray & (opponentPieces | friendlyPieces);

    if (!blockers) {
        return ray;
    }

    const uint64_t nearest = getRightMostBit(blockers);
    uint64_t moves = ray & ~(nearest - 1);

    if (nearest & friendlyPieces) {
        moves &= ~nearest;
    }

    return moves;
}

template<>
__attribute__((always_inline)) inline uint64_t MoveGenerator::getLegalMovesForRay<Direction::NW>(
    uint8_t from,
    uint64_t opponentPieces,
    uint64_t friendlyPieces
) {
    const uint64_t ray = raysNW[from];
    const uint64_t blockers = ray & (opponentPieces | friendlyPieces);

    if (!blockers) {
        return ray;
    }

    const uint64_t nearest = getRightMostBit(blockers);
    uint64_t moves = ray & ((nearest - 1) | nearest);

    if (nearest & friendlyPieces) {
        moves &= ~nearest;
    }

    return moves;
}

#endif