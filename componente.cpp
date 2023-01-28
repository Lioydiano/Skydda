#include "componente.hpp"

namespace skydda {

    Componente::Componente() : carattere(), coordinate(), stile(), tipo(__IGNOTO__) {}
    Componente::Componente(char carattere_, Coordinate coordinata_, ANSI::Stile stile_, TipoComponente tipo_) : carattere(carattere_), coordinate(coordinata_), stile(stile_), tipo(tipo_) {}
    TipoComponente Componente::getTipo() const {
        return this->tipo;
    }
    char Componente::getCarattere() const {
        return this->carattere;
    }
    void Componente::setCarattere(char carattere_) {
        this->carattere = carattere_;
    }
    Coordinate Componente::getCoordinate() const {
        return this->coordinate;
    }
    void Componente::setCoordinate(Coordinate coordinate_) {
        this->coordinate = coordinate_;
    }
    ANSI::Stile Componente::getStile() const {
        return this->stile;
    }
    void Componente::setStile(ANSI::Stile stile_) {
        this->stile = stile_;
    }
    void Componente::stampa() {
        this->stile.applica();
        std::cout << this->carattere;
    }
}