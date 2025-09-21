#ifndef MOVE_GENERATOR_TPP
#define MOVE_GENERATOR_TPP

#include <iostream>
#include "move_generator.h"
#include "../../Utils/utils.h"

template<>
__attribute__((always_inline)) inline uint64_t MoveGenerator::getLegalMovesForRay<Direction::N>(
    uint8_t from,
    uint64_t opponentPieces,
    uint64_t friendlyPieces
) {
    const uint64_t ray = raysN[from];

    uint64_t opponentBlocker = getRightMostBit(ray & opponentPieces);
    uint64_t friendlyBlocker = getRightMostBit(ray & friendlyPieces);

    if (friendlyBlocker) friendlyBlocker >>= 8; 
    
    uint64_t blocker = getRightMostBit(opponentBlocker | friendlyBlocker);
    if (!blocker) return ray;
    
    uint64_t mask = ray & ((blocker - 1) | blocker); 

    return mask;
}

template<>
__attribute__((always_inline)) inline uint64_t MoveGenerator::getLegalMovesForRay<Direction::NE>(
    uint8_t from,
    uint64_t opponentPieces,
    uint64_t friendlyPieces
) {
    const uint64_t ray = raysNE[from];

    uint64_t opponentBlocker = getRightMostBit(ray & opponentPieces);
    uint64_t friendlyBlocker = getRightMostBit(ray & friendlyPieces);

    if (friendlyBlocker) friendlyBlocker >>= 9; 
    
    uint64_t blocker = getRightMostBit(opponentBlocker | friendlyBlocker);
    if (!blocker) return ray;
    
    uint64_t mask = ray & ((blocker - 1) | blocker);

    return mask;
}

template<>
__attribute__((always_inline)) inline uint64_t MoveGenerator::getLegalMovesForRay<Direction::E>(
    uint8_t from,
    uint64_t opponentPieces,
    uint64_t friendlyPieces
) {
    const uint64_t ray = raysE[from];

    uint64_t opponentBlocker = getLeftMostBit(ray & opponentPieces);
    uint64_t friendlyBlocker = getLeftMostBit(ray & friendlyPieces);

    if (friendlyBlocker) friendlyBlocker >>= 1; 
    
    uint64_t blocker = getLeftMostBit(opponentBlocker | friendlyBlocker);
    if (!blocker) return ray;
    
    uint64_t mask = ray & ((blocker - 1) | blocker);

    return mask;
}

template<>
__attribute__((always_inline)) inline uint64_t MoveGenerator::getLegalMovesForRay<Direction::SE>(
    uint8_t from,
    uint64_t opponentPieces,
    uint64_t friendlyPieces
) {
    const uint64_t ray = raysSE[from];

    uint64_t opponentBlocker = getLeftMostBit(ray & opponentPieces);
    uint64_t friendlyBlocker = getLeftMostBit(ray & friendlyPieces);

    if (friendlyBlocker) friendlyBlocker <<= 7; 
    
    uint64_t blocker = getLeftMostBit(opponentBlocker | friendlyBlocker);
    if (!blocker) return ray;
    
    uint64_t mask = ray & ~(blocker - 1);

    return mask;
}

template<>
__attribute__((always_inline)) inline uint64_t MoveGenerator::getLegalMovesForRay<Direction::S>(
    uint8_t from,
    uint64_t opponentPieces,
    uint64_t friendlyPieces
) {
    const uint64_t ray = raysS[from];

    uint64_t opponentBlocker = getLeftMostBit(ray & opponentPieces);
    uint64_t friendlyBlocker = getLeftMostBit(ray & friendlyPieces);

    if (friendlyBlocker) friendlyBlocker <<= 8; 
    
    uint64_t blocker = getLeftMostBit(opponentBlocker | friendlyBlocker);
    if (!blocker) return ray;
    
    uint64_t mask = ray & ~(blocker - 1); 

    return mask;
}

template<>
__attribute__((always_inline)) inline uint64_t MoveGenerator::getLegalMovesForRay<Direction::SW>(
    uint8_t from,
    uint64_t opponentPieces,
    uint64_t friendlyPieces
) {
    const uint64_t ray = raysSW[from];

    uint64_t opponentBlocker = getLeftMostBit(ray & opponentPieces);
    uint64_t friendlyBlocker = getLeftMostBit(ray & friendlyPieces);

    if (friendlyBlocker) friendlyBlocker <<= 9; 
    
    uint64_t blocker = getLeftMostBit(opponentBlocker | friendlyBlocker);
    if (!blocker) return ray;
    
    uint64_t mask = ray & ~(blocker - 1);

    return mask;
}

template<>
__attribute__((always_inline)) inline uint64_t MoveGenerator::getLegalMovesForRay<Direction::W>(
    uint8_t from,
    uint64_t opponentPieces,
    uint64_t friendlyPieces
) {
    const uint64_t ray = raysW[from];

    uint64_t opponentBlocker = getRightMostBit(ray & opponentPieces);
    uint64_t friendlyBlocker = getRightMostBit(ray & friendlyPieces);

    if (friendlyBlocker) friendlyBlocker <<= 1; 
    
    uint64_t blocker = getRightMostBit(opponentBlocker | friendlyBlocker);
    if (!blocker) return ray;
    
    uint64_t mask = ray & ~(blocker - 1);

    return mask;
}

template<>
__attribute__((always_inline)) inline uint64_t MoveGenerator::getLegalMovesForRay<Direction::NW>(
    uint8_t from,
    uint64_t opponentPieces,
    uint64_t friendlyPieces
) {
    const uint64_t ray = raysNW[from];

    uint64_t opponentBlocker = getRightMostBit(ray & opponentPieces);
    uint64_t friendlyBlocker = getRightMostBit(ray & friendlyPieces);

    if (friendlyBlocker) friendlyBlocker >>= 7; 
    
    uint64_t blocker = getRightMostBit(opponentBlocker | friendlyBlocker);
    if (!blocker) return ray;
    
    uint64_t mask = ray & ((blocker - 1) | blocker);

    return mask;
}

#endif