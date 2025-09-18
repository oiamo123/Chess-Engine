#ifndef RAYGENERATOR_H
#define RAYGENERATOR_H

#include <cstdint>
#include <array>

using std::uint64_t;
using std::array;

class RayGenerator {
    public:
    static array<uint64_t, 64> generateNMasks();
    static array<uint64_t, 64> generateNEMasks();
    static array<uint64_t, 64> generateEMasks();
    static array<uint64_t, 64> generateSEMasks();
    static array<uint64_t, 64> generateSMasks();
    static array<uint64_t, 64> generateSWMasks();
    static array<uint64_t, 64> generateWMasks();
    static array<uint64_t, 64> generateNWMasks();
};

#endif