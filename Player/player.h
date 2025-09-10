#include <cstdint>
using std::int8_t;
using std::int64_t;

class Player {
    int8_t color;
    int64_t rooks;
    int64_t knights;
    int64_t bishops;
    int64_t pawns;
    int64_t queen;
    int64_t king;

    Player(
        int8_t color, 
        int64_t rooks, 
        int64_t knights, 
        int64_t bishops, 
        int64_t pawns, 
        int64_t queen, 
        int64_t king
    );
    
    int8_t getColor();
    int64_t getPawns();
    int64_t getRooks();
    int64_t getKnights();
    int64_t getBishops();
    int64_t getQueen();
    int64_t getKing();
    int64_t getAllPieces();
};