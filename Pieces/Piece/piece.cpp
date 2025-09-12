#include "./piece.h"
#include "../../Utils/utils.h"
#include <iostream>
using std::ostream;

Piece::Piece(int8_t type, int8_t color, uint64_t position) {
    this->type = type;
    this->color = color;
    this->position = position;
}

int8_t Piece::getType() {
    return type;
}

int8_t Piece::getColor() {
    return color;
}

uint64_t Piece::getPosition() {
    return position;
}

vector<int32_t> Piece::getMoves() {
    return vector<int32_t>();
}

std::ostream& operator<<(std::ostream& os, const Piece& piece) {
    os << "(piece="
       << Utils::getType(piece.type)
       << ", color=" << Utils::getColor(piece.color)
       << ", position=" << Utils::getSquare(piece.position)
       << ")";
    return os;
}