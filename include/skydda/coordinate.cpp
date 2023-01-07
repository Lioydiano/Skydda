#pragma once
#include <string>
#include "coordinate.hpp"
#include <fstream>
std::ofstream debug("debug.txt", std::ios::out);


namespace skydda {
    Coordinate::Coordinate() : y(0), x(0) {}
    Coordinate::Coordinate(unsigned short int y_, unsigned short int x_) : y(y_), x(x_) {}
    void Coordinate::valida(short int altezza, short int larghezza) {
        if (this->y < 0 || this->y >= altezza || this->x < 0 || this->x >= larghezza) {
            debug << "Coordinate non valide: (" << this->y << ", " << this->x << ")" << std::endl;
            throw std::runtime_error("Coordinate non valide (" + std::to_string(this->y) + ", " + std::to_string(this->x) + ")");
        }
    }
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