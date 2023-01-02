#pragma once
#include "componente.hpp"

namespace skydda {
    Componente::Componente() : carattere(), coordinate(), stile() {}
    Componente::Componente(char carattere_, Coordinate coordinata_, ANSI::Stile stile_) : carattere(carattere_), coordinate(coordinata_), stile(stile_) {}
    char Componente::getCarattere() const {
        return carattere;
    }
    void Componente::setCarattere(char carattere_) {
        carattere = carattere_;
    }
    Coordinate Componente::getCoordinate() const {
        return coordinate;
    }
    void Componente::setCoordinate(Coordinate coordinate_) {
        coordinate = coordinate_;
    }
    ANSI::Stile Componente::getStile() const {
        return stile;
    }
    void Componente::setStile(ANSI::Stile stile_) {
         stile = stile_;
    }
}