#include "./piece.h"
#include "../../Utils/utils.h"
#include <iostream>
using std::ostream;
using std::uint8_t;
using std::uint32_t;
using std::uint64_t;

Piece::Piece(uint8_t type, uint8_t color, uint64_t position) {
    this->type = type;
    this->color = color;
    this->position = position;
}

uint8_t Piece::getType() {
    return type;
}

uint8_t Piece::getColor() {
    return color;
}

uint64_t Piece::getPosition() {
    return position;
}

vector<uint32_t> Piece::getMoves() {
    return vector<uint32_t>();
}

std::ostream& operator<<(ostream& os, const Piece& piece) {
    os << "(piece="
       << Utils::getType(piece.type)
       << ", color=" << Utils::getColor(piece.color)
       << ", position=" << Utils::getSquare(piece.position)
       << ")";
    return os;
}