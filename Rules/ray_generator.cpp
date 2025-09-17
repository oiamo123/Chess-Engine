#include "./ray_generator.h"
#include "../Utils/utils.h"

map<uint64_t, uint64_t> RayGenerator::generateNMasks() {
    map<uint64_t, uint64_t> table;
    
    for (int8_t square = 0; square < 64; square++) {
        uint64_t from = 1ULL << square;
        uint64_t moves = 0ULL;

        const int rank = square / 8;
        const int file = square % 8;

        for (int r = rank + 1; r < 8; r++) {
            int targetSquare = r * 8 + file;
            moves |= Utils::indexToBitboard(targetSquare);
        }

        table[from] = moves;
    }

    return table;
}

map<uint64_t, uint64_t> RayGenerator::generateNEMasks() {
    map<uint64_t, uint64_t> table;

    for (int8_t square = 0; square < 64; square++) {
        uint64_t from = 1ULL << square;
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

        table[from] = moves;
    }

    return table;
}

map<uint64_t, uint64_t> RayGenerator::generateEMasks() {
    
    map<uint64_t, uint64_t> table;
    
    for (int8_t square = 0; square < 64; square++) {
        uint64_t from = 1ULL << square;
        uint64_t moves = 0ULL;

        const int rank = square / 8;
        const int file = square % 8;

        for (int f = file + 1; f < 8; f++) {
            int targetSquare = rank * 8 + f;
            moves |= Utils::indexToBitboard(targetSquare);
        }

        table[from] = moves;
    }

    return table;
}

map<uint64_t, uint64_t> RayGenerator::generateSEMasks() {
    map<uint64_t, uint64_t> table;

    for (int8_t square = 0; square < 64; square++) {
        uint64_t from = 1ULL << square;
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

        table[from] = moves;
    }

    return table;
}

map<uint64_t, uint64_t> RayGenerator::generateSMasks() {
    map<uint64_t, uint64_t> table;
    
    for (int8_t square = 0; square < 64; square++) {
        uint64_t from = 1ULL << square;
        uint64_t moves = 0ULL;

        const int rank = square / 8;
        const int file = square % 8;

        for (int r = rank - 1; r >= 0; r--) {
            int targetSquare = r * 8 + file;
            moves |= Utils::indexToBitboard(targetSquare);
        }

        table[from] = moves;
    }

    return table;
}

map<uint64_t, uint64_t> RayGenerator::generateSWMasks() {
    map<uint64_t, uint64_t> table;

    for (int8_t square = 0; square < 64; square++) {
        uint64_t from = 1ULL << square;
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

        table[from] = moves;
    }

    return table;
}

map<uint64_t, uint64_t> RayGenerator::generateWMasks() {
    
    map<uint64_t, uint64_t> table;
    
    for (int8_t square = 0; square < 64; square++) {
        uint64_t from = 1ULL << square;
        uint64_t moves = 0ULL;

        const int rank = square / 8;
        const int file = square % 8;

        for (int f = file - 1; f >= 0; f--) {
            int targetSquare = rank * 8 + f;
            moves |= Utils::indexToBitboard(targetSquare);
        }

        table[from] = moves;
    }

    return table;
}

map<uint64_t, uint64_t> RayGenerator::generateNWMasks() {
    map<uint64_t, uint64_t> table;

    for (int8_t square = 0; square < 64; square++) {
        uint64_t from = 1ULL << square;
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

        table[from] = moves;
    }

    return table;
}
