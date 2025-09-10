#include "./piece.h"
#include "../../Utils/utils.h"
#include <iostream>
using std::ostream;

Piece::Piece(int8_t type, int8_t color, int16_t position) {
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

int16_t Piece::getPosition() {
    return position;
}

vector<int16_t> Piece::getMoves() {
    return vector<int16_t>();
}

std::ostream& operator<<(std::ostream& os, const Piece& piece) {
    os << "("
       << Utils::pieceTypeToString(piece.type)
       << ", color=" << Utils::colorToString(piece.color)
       << ", position=" << piece.position
       << ")";
    return os;
}