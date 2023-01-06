#pragma once
#include "coordinate.hpp"


namespace skydda {
    Coordinate::Coordinate() : y(0), x(0) {}
    Coordinate::Coordinate(unsigned short int y_, unsigned short int x_) : y(y_), x(x_) {}
    Coordinate Coordinate::operator+(const Coordinate& coordinate) const {
        return Coordinate(this->y + coordinate.y, this->x + coordinate.x);
    }
    Coordinate Coordinate::operator*(int n) const {
        return Coordinate(this->y * n, this->x * n);
    }
    bool Coordinate::operator==(const Coordinate& coordinate) const {
        return this->y == coordinate.y && this->x == coordinate.x;
    }
};