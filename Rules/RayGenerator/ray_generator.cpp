#include "./ray_generator.h"
#include "../../Utils/utils.h"
using std::uint8_t;
using std::uint64_t;

array<uint64_t, 64> RayGenerator::generateNMasks() {
    array<uint64_t, 64> table;
    
    for (uint8_t square = 0; square < 64; square++) {
        uint64_t moves = 0ULL;

        const int rank = square / 8;
        const int file = square % 8;

        for (int r = rank + 1; r < 8; r++) {
            int targetSquare = r * 8 + file;
            moves |= Utils::indexToBitboard(targetSquare);
        }

        table[square] = moves;
    }

    return table;
}

array<uint64_t, 64> RayGenerator::generateNEMasks() {
    array<uint64_t, 64> table;

    for (uint8_t square = 0; square < 64; square++) {
        uint64_t moves = 0ULL;

        int r = square / 8;
        int f = square % 8;

        int rr = r + 1;
        int ff = f + 1;

        while (rr < 8 && ff < 8) {
            int targetSquare = rr * 8 + ff;
            moves |= Utils::indexToBitboard(targetSquare);
            rr++;
            ff++;
        }

        table[square] = moves;
    }

    return table;
}

array<uint64_t, 64> RayGenerator::generateEMasks() {
    array<uint64_t, 64> table;
    
    for (uint8_t square = 0; square < 64; square++) {
        uint64_t moves = 0ULL;

        const int rank = square / 8;
        const int file = square % 8;

        for (int f = file + 1; f < 8; f++) {
            int targetSquare = rank * 8 + f;
            moves |= Utils::indexToBitboard(targetSquare);
        }

        table[square] = moves;
    }

    return table;
}

array<uint64_t, 64> RayGenerator::generateSEMasks() {
    array<uint64_t, 64> table;

    for (uint8_t square = 0; square < 64; square++) {
        uint64_t moves = 0ULL;

        int r = square / 8;
        int f = square % 8;

        int rr = r - 1; 
        int ff = f + 1; 

        while (rr >= 0 && ff < 8) {
            int targetSquare = rr * 8 + ff;
            moves |= Utils::indexToBitboard(targetSquare);
            rr--;  
            ff++;  
        }

        table[square] = moves;
    }

    return table;
}

array<uint64_t, 64> RayGenerator::generateSMasks() {
    array<uint64_t, 64> table;
    
    for (uint8_t square = 0; square < 64; square++) {
        uint64_t moves = 0ULL;

        const int rank = square / 8;
        const int file = square % 8;

        for (int r = rank - 1; r >= 0; r--) {
            int targetSquare = r * 8 + file;
            moves |= Utils::indexToBitboard(targetSquare);
        }

        table[square] = moves;
    }

    return table;
}

array<uint64_t, 64> RayGenerator::generateSWMasks() {
    array<uint64_t, 64> table;

    for (uint8_t square = 0; square < 64; square++) {
        uint64_t moves = 0ULL;

        int r = square / 8;
        int f = square % 8;

        int rr = r - 1; 
        int ff = f - 1; 

        while (rr >= 0 && ff >= 0) {
            int targetSquare = rr * 8 + ff;
            moves |= Utils::indexToBitboard(targetSquare);
            rr--;  
            ff--;  
        }

        table[square] = moves;
    }

    return table;
}

array<uint64_t, 64> RayGenerator::generateWMasks() {
    
    array<uint64_t, 64> table;
    
    for (uint8_t square = 0; square < 64; square++) {
        uint64_t moves = 0ULL;

        const int rank = square / 8;
        const int file = square % 8;

        for (int f = file - 1; f >= 0; f--) {
            int targetSquare = rank * 8 + f;
            moves |= Utils::indexToBitboard(targetSquare);
        }

        table[square] = moves;
    }

    return table;
}

array<uint64_t, 64> RayGenerator::generateNWMasks() {
    array<uint64_t, 64> table;

    for (uint8_t square = 0; square < 64; square++) {
        uint64_t moves = 0ULL;

        int r = square / 8;
        int f = square % 8;

        int rr = r + 1; 
        int ff = f - 1; 

        while (rr < 8 && ff >= 0) {
            int targetSquare = rr * 8 + ff;
            moves |= Utils::indexToBitboard(targetSquare);
            rr++;  
            ff--;  
        }

        table[square] = moves;
    }

    return table;
}
