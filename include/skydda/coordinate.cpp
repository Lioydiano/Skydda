#pragma once
#include "coordinate.hpp"


namespace skydda {
    Coordinate::Coordinate() : y(0), x(0) {}
    Coordinate::Coordinate(unsigned short int y_, unsigned short int x_) : y(y_), x(x_) {}
    void Coordinate::valida(short int altezza, short int larghezza) {
        if (this->y < 0 || this->y >= altezza || this->x < 0 || this->x >= larghezza) { // Se sono fuori dai bordi...
            throw std::runtime_error("Coordinate non valide"); // ...Coordinate non valide (lancio un errore di runtime, che verrà gestito dal chiamante)
        }
    }
    Coordinate Coordinate::operator+(const Coordinate& coordinate) const {
        return Coordinate(this->y + coordinate.y, this->x + coordinate.x);
    }
    Coordinate Coordinate::operator*(int n) const { //cosa serve ?
        return Coordinate(this->y * n, this->x * n);
    }
    bool Coordinate::operator==(const Coordinate& coordinate) const {
        return this->y == coordinate.y && this->x == coordinate.x;
    }
}