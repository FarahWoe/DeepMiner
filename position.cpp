//
// Created by farah on 10.04.21.
//
#include "position.h"
Position::Position(int x, int y, int z) : x(x), y(y), z(z) {}

Position::Position() {}

Position::~Position() {

};

int Position::getX() const {
    return x;
}

void Position::setX(int x) {
    Position::x = x;
}

int Position::getY() const {
    return y;
}

void Position::setY(int y) {
    Position::y = y;
}

int Position::getZ() const {
    return z;
}

void Position::setZ(int z) {
    Position::z = z;
}
