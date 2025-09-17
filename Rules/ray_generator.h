#ifndef RAYGENERATOR_H
#define RAYGENERATOR_H

#include <cstdint>
#include <map>

using std::map;
using std::uint64_t;

class RayGenerator {
    public:
    static map<uint64_t, uint64_t> generateNMasks();
    static map<uint64_t, uint64_t> generateNEMasks();
    static map<uint64_t, uint64_t> generateEMasks();
    static map<uint64_t, uint64_t> generateSEMasks();
    static map<uint64_t, uint64_t> generateSMasks();
    static map<uint64_t, uint64_t> generateSWMasks();
    static map<uint64_t, uint64_t> generateWMasks();
    static map<uint64_t, uint64_t> generateNWMasks();
};

#endif