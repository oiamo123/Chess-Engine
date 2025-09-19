#include <iostream>
#include "./Utils/utils.h"
#include "./Rules/MoveGenerator/move_generator.h"

using std::cout;
using std::endl;
using std::uint8_t;
using std::uint32_t;

int main() {
    MoveGenerator moveGenerator = MoveGenerator();
    // const array<uint64_t, 64> knightMoves = moveGenerator.generateKnightTable();

    // for (int8_t i = 0; i < 63; i++) {
    //     Utils::printBitboard(knightMoves[i] | (1ULL << i));
    // }

    return 0;
}
