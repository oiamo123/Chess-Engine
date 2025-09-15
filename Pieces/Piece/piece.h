#ifndef PIECE_H
#define PIECE_H
#include <cstdint>
#include <string>
#include <vector>
using std::int8_t;
using std::int16_t;
using std::uint64_t;
using std::string;
using std::vector;
using std::ostream;

class Piece {
    public:
    int8_t type;
    int8_t color;
    uint64_t position;

    Piece(int8_t type, int8_t color, uint64_t position);
    int8_t getType();
    int8_t getColor();
    uint64_t getPosition();
    virtual vector<int32_t> getMoves();
    friend ostream& operator<<(ostream& os, const Piece& piece);
};

#endif