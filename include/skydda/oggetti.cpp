#pragma once
#include "ANSI.cpp"
#include "cursore.cpp"
#include "componente.cpp"
#include "oggetti.hpp"


namespace skydda {
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
        ANSI::ColoreSfondo::S_ROSSO,
        ANSI::Attributo::LUMINOSO
    );
    ANSI::Stile stileProiettileNemico(
        ANSI::ColoreTesto::CIANO,
        ANSI::ColoreSfondo::S_NERO,
        ANSI::Attributo::LUMINOSO
    );
    std::unordered_map<TipoProiettile, ANSI::Stile> stiliProiettile = {
        {TipoProiettile::P_DIFENSORE, stileProiettileDifensore},
        {TipoProiettile::P_NEMICO, stileProiettileNemico}
    };

    ANSI::Stile stileNemico(
        ANSI::ColoreTesto::BLU,
        ANSI::ColoreSfondo::S_NERO,
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
    void Nemico::stampa() {
        stile.applica();
        std::cout << vita;
    }

    ANSI::Stile stileDifensore(
        ANSI::ColoreTesto::VERDE,
        ANSI::ColoreSfondo::S_NERO,
        ANSI::Attributo::LUMINOSO
    );
    Difensore::Difensore(): Componente('1', Coordinate(0, 0), stileDifensore, TipoComponente::DIFENSORE) {} 
    Difensore::~Difensore() {}
    void Difensore::stampa() {
        std::cout << u8"安";
    }

    Proiettile::Proiettile() : Componente(direzioneCarattere[EST], Coordinate(0, 0), stileProiettileDifensore, TipoComponente::PROIETTILE_DIFENSORE), origine(TipoProiettile::P_DIFENSORE), direzione(EST), velocita(1) {}
    Proiettile::Proiettile(Coordinate coordinate_, TipoProiettile tipo_, Direzione direzione_, int velocita_) : Componente(direzioneCarattere[direzione_], coordinate_, stiliProiettile[tipo_], TipoComponente::PROIETTILE_DIFENSORE), origine(tipo_), direzione(direzione_), velocita(velocita_) {}
    Proiettile::~Proiettile() {}

    ANSI::Stile stileTerreno(
        ANSI::ColoreTesto::ROSSO,
        ANSI::ColoreSfondo::S_ROSSO,
        ANSI::Attributo::FLEBILE
    );
    Terreno::Terreno() : Componente(' ', Coordinate(0, 0), stileTerreno, TipoComponente::TERRENO) {}
    Terreno::Terreno(Coordinate coordinate_) : Componente(' ', coordinate_, stileTerreno, TipoComponente::TERRENO) {}
    Terreno::~Terreno() {}

    ANSI::Stile stileEffimera(
        ANSI::ColoreTesto::BIANCO,
        ANSI::ColoreSfondo::S_NERO,
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
    void Mappa::spostaComponente(Coordinate& partenza, Coordinate& arrivo) {
        if (mappa[arrivo.y][arrivo.x] == nullptr) {
            mappa[arrivo.y][arrivo.x] = mappa[partenza.y][partenza.x];
            mappa[partenza.y][partenza.x] = nullptr;
        } else {
            switch (mappa[partenza.y][partenza.x]->getTipo()) {
                case TipoComponente::DIFENSORE: { // Collisione Difensore - ???
                    switch (mappa[arrivo.y][arrivo.x]->getTipo()) {
                        case TipoComponente::PROIETTILE_NEMICO: { // Collisione Difensore - Proiettile nemico
                            // Morte del Difensore
                            mappa[arrivo.y][arrivo.x] = mappa[partenza.y][partenza.x];
                            mappa[partenza.y][partenza.x] = nullptr;
                            cancellaComponente(partenza);
                            stampaComponente(arrivo);
                            exit(0); // Fine del gioco
                        }
                        case TipoComponente::TERRENO: case TipoComponente::EFFIMERA: { // Collisione Difensore - Terreno | Effimera
                            immettiComponente(mappa[partenza.y][partenza.x], arrivo);
                            immettiComponente(new Terreno(partenza), partenza);
                            stampaComponente(partenza);
                            stampaComponente(arrivo);
                        }
                        default:
                            break;
                    }
                    break;
                }
                case TipoComponente::NEMICO: { // Collisione Nemico - ???
                    switch (mappa[arrivo.y][arrivo.x]->getTipo()) {
                        case TipoComponente::PROIETTILE_DIFENSORE: { // Collisione Nemico - Proiettile difensore
                            // Decremento del Nemico
                            delete mappa[arrivo.y][arrivo.x]; // Deallocazione della memoria del proiettile
                            Nemico* nemico = (Nemico*)mappa[partenza.y][partenza.x];
                            immettiComponente(nemico, arrivo);
                            nemico->setVita(std::max(nemico->getVita() - 1, 9));
                            nemico->setCoordinate(arrivo);
                            mappa[partenza.y][partenza.x] = nullptr;
                            cancellaComponente(partenza);
                            stampaComponente(arrivo);
                        }
                        case TipoComponente::PROIETTILE_NEMICO: { // Collisione Nemico - Proiettile nemico
                            // Incremento del Nemico
                            delete mappa[arrivo.y][arrivo.x]; // Deallocazione della memoria del proiettile
                            Nemico* nemico = (Nemico*)mappa[partenza.y][partenza.x];
                            immettiComponente(nemico, arrivo);
                            nemico->setVita(std::max(nemico->getVita() + 1, 9));
                            nemico->setCoordinate(arrivo);
                            mappa[partenza.y][partenza.x] = nullptr;
                            cancellaComponente(partenza);
                            stampaComponente(arrivo);
                        }
                        case TipoComponente::NEMICO: { // Collisione Nemico - Nemico
                            // Somma dei due Nemici
                            Nemico* nemico1 = (Nemico*)mappa[partenza.y][partenza.x];
                            Nemico* nemico2 = (Nemico*)mappa[arrivo.y][arrivo.x];
                            immettiComponente(nemico1, arrivo);
                            nemico1->setVita(std::max(nemico1->getVita() + nemico2->getVita(), 9));
                            nemico1->setCoordinate(arrivo);
                            mappa[partenza.y][partenza.x] = nullptr;
                            cancellaComponente(partenza);
                            stampaComponente(arrivo);
                            delete nemico2; // Deallocazione della memoria del nemico
                        }
                        case TipoComponente::EFFIMERA: { // Collisione Nemico - Effimera
                            // Morte del Nemico
                            delete mappa[arrivo.y][arrivo.x]; // Deallocazione della memoria dell'effimera
                            mappa[arrivo.y][arrivo.x] = mappa[partenza.y][partenza.x];
                            mappa[partenza.y][partenza.x] = nullptr;
                            cancellaComponente(partenza);
                            stampaComponente(arrivo);
                        }
                        default:
                            break;
                    }
                    break;
                }
                case TipoComponente::PROIETTILE_DIFENSORE: { // Collisione Proiettile difensore - ???
                    switch (mappa[arrivo.y][arrivo.x]->getTipo()) {
                        case TipoComponente::NEMICO: { // Collisione Proiettile difensore - Nemico
                            // Decremento del Nemico
                            ProiettileDifensore* proiettile = (ProiettileDifensore*)mappa[partenza.y][partenza.x];
                            Nemico* nemico = (Nemico*)mappa[arrivo.y][arrivo.x];
                            nemico->setVita(std::max(nemico->getVita() - 1, 9));
                            if (proiettile->getSopraTerreno()) {
                                // Il proiettile si trova sull'isola, quindi sul Terreno che va ripristinato
                                immettiComponente(new Terreno(partenza), partenza);
                            }
                            delete proiettile; // Deallocazione della memoria del proiettile
                            stampaComponente(arrivo);
                            stampaComponente(partenza);
                        }
                        case TipoComponente::PROIETTILE_NEMICO: { // Collisione Proiettile difensore - Proiettile nemico
                            // Distruzione dei due proiettili e creazione dell'effimera
                            delete mappa[arrivo.y][arrivo.x]; // Deallocazione della memoria del proiettile nemico
                            delete mappa[partenza.y][partenza.x]; // Deallocazione della memoria del proiettile difensore
                            immettiComponente(new Effimera(arrivo), arrivo);
                            effimere.push((Effimera*)mappa[arrivo.y][arrivo.x]);
                            stampaComponente(arrivo);
                            cancellaComponente(partenza);
                        }
                        case TipoComponente::TERRENO: { // Collisione Proiettile difensore - Terreno
                            // Spostamento del proiettile sul Terreno
                            ProiettileDifensore* proiettile = (ProiettileDifensore*)mappa[partenza.y][partenza.x];
                            if (proiettile->getSopraTerreno()) {
                                // Il proiettile si trova sull'isola, quindi sul Terreno che va ripristinato
                                immettiComponente(new Terreno(partenza), partenza);
                                proiettile->setSopraTerreno(false);
                            } else {
                                mappa[partenza.y][partenza.x] = nullptr;
                            }
                            delete mappa[arrivo.y][arrivo.x]; // Deallocazione della memoria del terreno
                            immettiComponente(proiettile, arrivo);
                            cancellaComponente(partenza);
                            stampaComponente(arrivo);
                            proiettile->setSopraTerreno(true);
                        }
                        default:
                            break;
                    }
                    break;
                }
                case TipoComponente::PROIETTILE_NEMICO: { // Collisione Proiettile nemico - ???
                    switch (mappa[arrivo.y][arrivo.x]->getTipo()) {
                        case TipoComponente::TERRENO: { // Collisione Proiettile nemico - Terreno
                            // Spostamento del proiettile sul Terreno
                            delete mappa[arrivo.y][arrivo.x]; // Deallocazione della memoria del terreno
                            delete mappa[partenza.y][partenza.x]; // Deallocazione della memoria del proiettile nemico
                            mappa[partenza.y][partenza.x] = nullptr;
                            immettiComponente(new Effimera(arrivo), arrivo);
                            effimere.push((Effimera*)mappa[arrivo.y][arrivo.x]);
                            cancellaComponente(partenza);
                            stampaComponente(arrivo);
                        }
                        case TipoComponente::PROIETTILE_DIFENSORE: { // Collisione Proiettile nemico - Proiettile difensore
                            // Distruzione dei due proiettili e creazione dell'effimera
                            delete mappa[arrivo.y][arrivo.x]; // Deallocazione della memoria del proiettile difensore
                            delete mappa[partenza.y][partenza.x]; // Deallocazione della memoria del proiettile nemico
                            immettiComponente(new Effimera(arrivo), arrivo);
                            effimere.push((Effimera*)mappa[arrivo.y][arrivo.x]);
                            stampaComponente(arrivo);
                            cancellaComponente(partenza);
                        }
                        case TipoComponente::NEMICO: { // Collisione Proiettile nemico - Nemico
                            // Incremento del Nemico
                            delete mappa[partenza.y][partenza.x]; // Deallocazione della memoria del proiettile nemico
                            mappa[partenza.y][partenza.x] = nullptr;
                            Nemico* nemico = (Nemico*)mappa[arrivo.y][arrivo.x];
                            nemico->setVita(std::max(nemico->getVita() + 1, 9));
                            stampaComponente(arrivo);
                            cancellaComponente(partenza);
                        }
                        default:
                            break;
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }
    ANSI::Stile stileBordo(
        ANSI::ColoreTesto::BIANCO,
        ANSI::ColoreSfondo::S_GIALLO,
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