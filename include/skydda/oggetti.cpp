#pragma once
#include "ANSI.cpp"
#include "cursore.cpp"
#include "componente.cpp"
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
    ANSI::Stile stileProiettileDifensore(
        ANSI::ColoreTesto::MAGENTA,
        ANSI::ColoreSfondo::ROSSO,
        ANSI::Attributo::LUMINOSO
    );
    ANSI::Stile stileProiettileNemico(
        ANSI::ColoreTesto::CIANO,
        ANSI::ColoreSfondo::NERO,
        ANSI::Attributo::LUMINOSO
    );
    std::unordered_map<TipoProiettile, ANSI::Stile> stiliProiettile = {
        {DIFENSORE, stileProiettileDifensore},
        {NEMICO, stileProiettileNemico}
    };

    ANSI::Stile stileNemico(
        ANSI::ColoreTesto::BLU,
        ANSI::ColoreSfondo::NERO,
        ANSI::Attributo::LUMINOSO
    );
    Nemico::Nemico() : Componente('1', Coordinate(0, 0), stileNemico, TipoComponente::NEMICO), vita(1) {} 
    Nemico::Nemico(char carattere_, Coordinate coordinate_, short int vita_) : Componente(carattere_, coordinate_, stileNemico, TipoComponente::NEMICO), vita(vita_) {}
    Nemico::~Nemico() {}
    void Nemico::setVita(short int vita_) {
        vita = vita_;
    }
    short int Nemico::getVita() const {
        return vita;
    }

    ANSI::Stile stileDifensore(
        ANSI::ColoreTesto::VERDE,
        ANSI::ColoreSfondo::NERO,
        ANSI::Attributo::LUMINOSO
    );
    Difensore::Difensore(): Componente('1', Coordinate(0, 0), stileDifensore, TipoComponente::DIFENSORE) {} 
    Difensore::~Difensore() {}
    void Difensore::stampa() {
        std::cout << u8"安";
    }

    Proiettile::Proiettile() : Componente(direzioneCarattere[EST], Coordinate(0, 0), stileProiettileDifensore, TipoComponente::PROIETTILE_DIFENSORE), origine(DIFENSORE), direzione(EST), velocita(1) {}
    Proiettile::Proiettile(Coordinate coordinate_, TipoProiettile tipo_, Direzione direzione_, int velocita_) : Componente(direzioneCarattere[direzione_], coordinate_, stiliProiettile[tipo_], TipoComponente::PROIETTILE_DIFENSORE), origine(tipo_), direzione(direzione_), velocita(velocita_) {}
    Proiettile::~Proiettile() {}

    ANSI::Stile stileTerreno(
        ANSI::ColoreTesto::ROSSO,
        ANSI::ColoreSfondo::ROSSO,
        ANSI::Attributo::FLEBILE
    );
    Terreno::Terreno() : Componente(' ', Coordinate(0, 0), stileTerreno, TipoComponente::TERRENO) {}
    Terreno::Terreno(Coordinate coordinate_) : Componente(' ', coordinate_, stileTerreno, TipoComponente::TERRENO) {}
    Terreno::~Terreno() {}

    ANSI::Stile stileEffimera(
        ANSI::ColoreTesto::BIANCO,
        ANSI::ColoreSfondo::NERO,
        ANSI::Attributo::FLEBILE
    );
    Effimera::Effimera() : Componente(' ', Coordinate(0, 0), stileEffimera, TipoComponente::EFFIMERA) {}
    Effimera::Effimera(Coordinate coordinate_) : Componente(' ', coordinate_, stileEffimera, TipoComponente::EFFIMERA) {}
    Effimera::~Effimera() {}
    void Effimera::stampa() {
        std::cout << u8"💥";
    }

    Mappa::Mappa() : larghezza(0), altezza(0) {}
    Mappa::Mappa(short int larghezza_, short int altezza_) : larghezza(larghezza_), altezza(altezza_) {
        mappa.resize(altezza);
        for (int i = 0; i < altezza; i++) {
            mappa[i].resize(larghezza);
        }
    }
    Mappa::~Mappa() {
        for (int i = 0; i < altezza; i++) {
            for (int j = 0; j < larghezza; j++) {
                if (mappa[i][j] != nullptr)
                    delete mappa[i][j]; // Deallocazione della memoria
            }
        }
    }
    short int Mappa::getAltezza() const {
        return altezza;
    }
    short int Mappa::getLarghezza() const {
        return larghezza;
    }
    Componente* Mappa::getComponente(Coordinate& coordinate) const {
        return mappa[coordinate.y][coordinate.x];
    }
    void Mappa::immettiComponente(Componente* componente, Coordinate& coordinate) {
        mappa[coordinate.y][coordinate.x] = componente;
    }
    void Mappa::immettiComponente(Componente* componente) {
        mappa[componente->getCoordinate().y][componente->getCoordinate().x] = componente;
    }
    void Mappa::rimuoviComponente(Coordinate& coordinate) {
        delete mappa[coordinate.y][coordinate.x];
        mappa[coordinate.y][coordinate.x] = nullptr;
    }
    void Mappa::rimuoviComponente(Componente* componente) {
        mappa[componente->getCoordinate().y][componente->getCoordinate().x] = nullptr;
    }
    void Mappa::stampaComponente(Coordinate& coordinate) {
        cursore.posiziona(coordinate);
        if (mappa[coordinate.y][coordinate.x] != nullptr)
            mappa[coordinate.y][coordinate.x]->stampa();
        else
            std::cout << ' ';
    }
    void Mappa::stampaComponente(Componente* componente) {
        cursore.posiziona(componente->getCoordinate());
        if (componente != nullptr)
            componente->stampa();
        else
            std::cout << ' ';
    }
    void Mappa::cancellaComponente(Coordinate& coordinate) {
        cursore.posiziona(coordinate);
        ANSI::reimposta();
        std::cout << ' ';
    }
    void Mappa::cancellaComponente(Componente* componente) {
        cursore.posiziona(componente->getCoordinate());
        ANSI::reimposta();
        std::cout << ' ';
    }
    ANSI::Stile stileBordo(
        ANSI::ColoreTesto::BIANCO,
        ANSI::ColoreSfondo::GIALLO,
        ANSI::Attributo::LUMINOSO
    );
    void Mappa::stampa() const {
        pulisciSchermo();
        stileBordo.applica();
        for (int i = 0; i < altezza; i++) {
            bool spazioPrecedente = false; // Serve per evitare di ripristinare lo stile ANSI ogni volta che si stampa uno spazio
            std::cout << '@';
            for (int j = 0; j < larghezza; j++) {
                if (mappa[i][j] != nullptr) {
                    spazioPrecedente = false;
                    mappa[i][j]->stampa();
                } else {
                    if (spazioPrecedente) {
                        std::cout << ' ';
                    } else {
                        spazioPrecedente = true;
                        std::cout << ' ';
                    }
                }
            }
            stileBordo.applica();
            std::cout << '@';
            std::cout << '\n';
        }
        ANSI::reimposta();
        std::flush(std::cout);
    }
};