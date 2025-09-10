#include <cstdint>
#include <string>
#include <vector>
using std::int8_t;
using std::int16_t;
using std::int64_t;
using std::string;
using std::vector;

class Piece {
    public:
    int8_t type;
    int8_t color;
    int16_t position;

    Piece(int8_t type, int8_t color, int16_t position);
    int8_t getType();
    int8_t getColor();
    int16_t getPosition();
    virtual vector<int16_t> getMoves();
    friend std::ostream& operator<<(std::ostream& os, const Piece& piece);
};