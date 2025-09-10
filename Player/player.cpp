#include "./player.h"

Player::Player(
    int8_t color, 
    int64_t rooks, 
    int64_t knights, 
    int64_t bishops, 
    int64_t pawns, 
    int64_t queen, 
    int64_t king
) {
    this->color = color;
    this->rooks = rooks;
    this->knights = knights;
    this->bishops = bishops;
    this->pawns = pawns;
    this->queen = queen;
    this->king = king;
}

int8_t Player::getColor() {
    return color;
}

int64_t Player::getPawns() {
    return pawns;
}

int64_t Player::getRooks() {
    return rooks;
}

int64_t Player::getKnights() {
    return knights;
}

int64_t Player::getBishops() {
    return bishops;
}

int64_t Player::getQueen() {
    return queen;
}

int64_t Player::getKing() {
    return king;
}

int64_t Player::getAllPieces() {
    return rooks | knights | bishops | pawns | queen | king;
}