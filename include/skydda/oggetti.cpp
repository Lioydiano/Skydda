#pragma once
#include "ANSI.cpp"
#include "oggetti.hpp"


namespace skydda {
    enum Direzione { NORD, EST, SUD, OVEST };
    enum TipoProiettile { DIFENSORE, NEMICO };
    std::unordered_map<Direzione, Coordinate> direzioni = {
        {NORD, Coordinate(0, -1)},
        {EST, Coordinate(1, 0)},
        {SUD, Coordinate(0, 1)},
        {OVEST, Coordinate(-1, 0)}
    };
    std::unordered_map<Direzione, char> direzioneCarattere = {
        {NORD, '^'},
        {EST, '>'},
        {SUD, 'v'},
        {OVEST, '<'}
    };

    ANSI::Stile stileTerreno(
        ANSI::ColoreTesto::ROSSO,
        ANSI::ColoreSfondo::ROSSO,
        ANSI::Attributo::FLEBILE
    );
    Terreno::Terreno() : Componente(' ', Coordinate(0, 0), stileTerreno) {}
    Terreno::Terreno(Coordinate coordinate_) : Componente(' ', coordinate_, stileTerreno) {}
    Terreno::~Terreno() {}

    ANSI::Stile stileEffimera(
        ANSI::ColoreTesto::BIANCO,
        ANSI::ColoreSfondo::NERO,
        ANSI::Attributo::FLEBILE
    );
    Effimera::Effimera() : Componente(' ', Coordinate(0, 0), stileEffimera) {}
    Effimera::Effimera(Coordinate coordinate_) : Componente(' ', coordinate_, stileEffimera) {}
    Effimera::~Effimera() {}
    void Effimera::stampa() {
        std::cout << u8"💥";
    }
};