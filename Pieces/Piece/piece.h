#ifndef PIECE_H
#define PIECE_H
#include <cstdint>
#include <string>
#include <vector>
using std::uint8_t;
using std::uint16_t;
using std::uint64_t;
using std::string;
using std::vector;
using std::ostream;

class Piece {
    public:
    uint8_t type;
    uint8_t color;
    uint64_t position;

    Piece(uint8_t type, uint8_t color, uint64_t position);
    uint8_t getType();
    uint8_t getColor();
    uint64_t getPosition();
    virtual vector<uint32_t> getMoves();
    friend ostream& operator<<(ostream& os, const Piece& piece);
};

#endif