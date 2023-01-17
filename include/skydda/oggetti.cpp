#pragma once
#include <algorithm>
#include "ANSI.cpp"
#include "cursore.cpp"
#include "componente.cpp"
#include "oggetti.hpp"

namespace skydda {
    std::unordered_map<Direzione, Coordinate> direzioni = {
        {NORD, Coordinate(-1, 0)},
        {EST, Coordinate(0, 1)},
        {SUD, Coordinate(1, 0)},
        {OVEST, Coordinate(0, -1)}
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

    ANSI::Stile stileDifensore(
        ANSI::ColoreTesto::VERDE,
        ANSI::ColoreSfondo::S_ROSSO,
        ANSI::Attributo::LUMINOSO
    );
    Difensore::Difensore(): Componente('1', Coordinate(0, 0), stileDifensore, TipoComponente::DIFENSORE) {} 
    Difensore::~Difensore() {}
    void Difensore::stampa() {
        stile.applica();
        std::cout << u8"$";
    }

    Proiettile::Proiettile() : Componente(direzioneCarattere[EST], Coordinate(0, 0), stileProiettileDifensore, TipoComponente::PROIETTILE_DIFENSORE), origine(TipoProiettile::P_DIFENSORE), direzione(EST), velocita(1) {}
    Proiettile::Proiettile(Coordinate coordinate_, TipoProiettile tipo_, Direzione direzione_, int velocita_) : Componente(direzioneCarattere[direzione_], coordinate_, stiliProiettile[tipo_], TipoComponente::PROIETTILE_DIFENSORE), origine(tipo_), direzione(direzione_), velocita(velocita_) {
        this->tipo = tipo_ == TipoProiettile::P_DIFENSORE ? TipoComponente::PROIETTILE_DIFENSORE : TipoComponente::PROIETTILE_NEMICO;
    }
    Proiettile::Proiettile(char carattere_, Coordinate coordinate_, TipoProiettile tipo_, Direzione direzione_, int velocita_) : Componente(carattere_, coordinate_, stiliProiettile[tipo_], TipoComponente::PROIETTILE_DIFENSORE), origine(tipo_), direzione(direzione_), velocita(velocita_) {
        this->tipo = tipo_ == TipoProiettile::P_DIFENSORE ? TipoComponente::PROIETTILE_DIFENSORE : TipoComponente::PROIETTILE_NEMICO;
    }
    Proiettile::~Proiettile() {}
    TipoProiettile Proiettile::getOrigine() const {
        return origine;
    }
    Direzione Proiettile::getDirezione() const {
        return direzione;
    }
    void Proiettile::setDirezione(Direzione direzione_) {
        direzione = direzione_;
        carattere = direzioneCarattere[direzione];
    }
    int Proiettile::getVelocita() const {
        return velocita;
    }
    Coordinate Proiettile::calcolaProssimaPosizione() const {
        return coordinate + direzioni[direzione] * velocita;
    }

    ProiettileDifensore::ProiettileDifensore() : Proiettile() {}
    ProiettileDifensore::ProiettileDifensore(Coordinate coordinate_, Direzione direzione_, int velocita_, bool sopraTerreno_=true) : Proiettile(coordinate_, TipoProiettile::P_DIFENSORE, direzione_, velocita_), sopraTerreno(sopraTerreno_) {
        stile.coloreSfondo = !sopraTerreno ? ANSI::ColoreSfondo::S_NERO : ANSI::ColoreSfondo::S_ROSSO;
    }
    ProiettileDifensore::ProiettileDifensore(char carattere_, Coordinate coordinate_, Direzione direzione_, int velocita_, bool sopraTerreno_=true) : Proiettile(carattere_, coordinate_, TipoProiettile::P_DIFENSORE, direzione_, velocita_), sopraTerreno(sopraTerreno_) {
        stile.coloreSfondo = !sopraTerreno ? ANSI::ColoreSfondo::S_NERO : ANSI::ColoreSfondo::S_ROSSO;
    }
    ProiettileDifensore::~ProiettileDifensore() {}
    bool ProiettileDifensore::getSopraTerreno() const {
        return sopraTerreno;
    }
    void ProiettileDifensore::setSopraTerreno(bool sopraTerreno_) {
        sopraTerreno = sopraTerreno_;
        stile.coloreSfondo = !sopraTerreno ? ANSI::ColoreSfondo::S_NERO : ANSI::ColoreSfondo::S_ROSSO;
    }

    ProiettileNemico::ProiettileNemico() : Proiettile() {}
    ProiettileNemico::ProiettileNemico(Coordinate coordinate_, Direzione direzione_, int velocita_) : Proiettile(coordinate_, TipoProiettile::P_NEMICO, direzione_, velocita_) {}
    ProiettileNemico::ProiettileNemico(char carattere_, Coordinate coordinate_, Direzione direzione_, int velocita_) : Proiettile(carattere_, coordinate_, TipoProiettile::P_NEMICO, direzione_, velocita_) {}
    ProiettileNemico::~ProiettileNemico() {}

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
    void stampaEffimera(Coordinate& coordinate) {
        std::cout << CSI << coordinate.y + 2 << ";" << coordinate.x + 2 << "H";
        stileEffimera.applica();
        std::cout << u8"*";
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
    void Mappa::registraComponente(Proiettile* proiettile) {
        proiettili.push_back(proiettile);
        immettiComponente(proiettile);
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
        try {
            arrivo.valida(altezza, larghezza);
        } catch (std::runtime_error& e) {
            switch (mappa[partenza.y][partenza.x]->getTipo()) {
                case TipoComponente::PROIETTILE_DIFENSORE: {
                    proiettili.erase(std::find(proiettili.begin(), proiettili.end(), (Proiettile*)mappa[partenza.y][partenza.x]));
                    if (((ProiettileDifensore*)mappa[partenza.y][partenza.x])->getSopraTerreno()) {
                        immettiComponente(new Terreno(partenza), partenza);
                        stampaComponente(partenza);
                    } else {
                        rimuoviComponente(partenza);
                        cancellaComponente(partenza);
                    }
                    break;
                }
                case TipoComponente::PROIETTILE_NEMICO: {
                    proiettili.erase(std::find(proiettili.begin(), proiettili.end(), (Proiettile*)mappa[partenza.y][partenza.x]));
                    rimuoviComponente(partenza);
                    cancellaComponente(partenza);
                    break;
                }
                case TipoComponente::DIFENSORE: {
                    break;
                }
                default:
                    break;
            }
            return;
        }
        if (mappa[arrivo.y][arrivo.x] == nullptr) {
            Componente* componente = mappa[partenza.y][partenza.x];
            mappa[partenza.y][partenza.x] = nullptr;
            componente->setCoordinate(arrivo);
            mappa[arrivo.y][arrivo.x] = componente;
            if (mappa[arrivo.y][arrivo.x]->getTipo() == TipoComponente::PROIETTILE_DIFENSORE) {
                if (((ProiettileDifensore*)mappa[arrivo.y][arrivo.x])->getSopraTerreno()) {
                    immettiComponente(new Terreno(partenza), partenza);
                    ((ProiettileDifensore*)mappa[arrivo.y][arrivo.x])->setSopraTerreno(false);
                    stampaComponente(partenza);
                } else {
                    cancellaComponente(partenza);
                }
            } else {
                cancellaComponente(partenza);
            }
            stampaComponente(arrivo);
        } else {
            switch (mappa[partenza.y][partenza.x]->getTipo()) {
                case TipoComponente::DIFENSORE: { // Collisione Difensore - ???
                    switch (mappa[arrivo.y][arrivo.x]->getTipo()) {
                        case TipoComponente::PROIETTILE_NEMICO: { // Collisione Difensore - Proiettile nemico
                            // Morte del Difensore
                            mappa[arrivo.y][arrivo.x] = mappa[partenza.y][partenza.x];
                            mappa[arrivo.y][arrivo.x]->setCoordinate(arrivo);
                            mappa[partenza.y][partenza.x] = nullptr;
                            cancellaComponente(partenza);
                            stampaComponente(arrivo);
                            exit(0); // Fine del gioco
                        }
                        case TipoComponente::TERRENO: { // Collisione Difensore - Terreno | Effimera
                            immettiComponente(mappa[partenza.y][partenza.x], arrivo);
                            immettiComponente(new Terreno(partenza), partenza);
                            mappa[arrivo.y][arrivo.x]->setCoordinate(arrivo);
                            stampaComponente(partenza);
                            stampaComponente(arrivo);
                        }
                        default:
                            break;
                    }
                    break;
                }
                case TipoComponente::PROIETTILE_DIFENSORE: { // Collisione Proiettile difensore - ???
                    switch (mappa[arrivo.y][arrivo.x]->getTipo()) {
                        case TipoComponente::PROIETTILE_NEMICO: { // Collisione Proiettile difensore - Proiettile nemico
                            // Distruzione dei due proiettili e creazione dell'effimera
                            ProiettileDifensore* proiettile = (ProiettileDifensore*)mappa[partenza.y][partenza.x];
                            bool sopraTerreno_ = proiettile->getSopraTerreno();
                            proiettili.erase(std::find(proiettili.begin(), proiettili.end(), proiettile));
                            proiettili.erase(std::find(proiettili.begin(), proiettili.end(), (Proiettile*)mappa[arrivo.y][arrivo.x]));
                            delete proiettile; // Deallocazione della memoria del proiettile difensore
                            rimuoviComponente(arrivo); // Deallocazione della memoria del proiettile nemico
                            if (sopraTerreno_) {
                                // Il proiettile si trova sull'isola, quindi sul Terreno che va ripristinato
                                immettiComponente(new Terreno(partenza), partenza);
                                stampaComponente(partenza);
                            } else {
                                mappa[partenza.y][partenza.x] = nullptr;
                                cancellaComponente(partenza);
                            }
                            stampaEffimera(arrivo);
                            break;
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
                            proiettile->setCoordinate(arrivo);
                            proiettile->setSopraTerreno(true);
                            immettiComponente(proiettile, arrivo);
                            stampaComponente(partenza);
                            stampaComponente(arrivo);
                            break;
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
                            rimuoviComponente(arrivo); // Deallocazione della memoria del terreno
                            proiettili.erase(std::find(proiettili.begin(), proiettili.end(), (Proiettile*)mappa[partenza.y][partenza.x]));
                            rimuoviComponente(partenza); // Rimozione del proiettile dal vettore dei componenti
                            cancellaComponente(partenza);
                            stampaEffimera(arrivo);
                            break;
                        }
                        case TipoComponente::PROIETTILE_DIFENSORE: { // Collisione Proiettile nemico - Proiettile difensore
                            // Distruzione dei due proiettili e creazione dell'effimera
                            proiettili.erase(std::find(proiettili.begin(), proiettili.end(), (Proiettile*)mappa[partenza.y][partenza.x]));
                            proiettili.erase(std::find(proiettili.begin(), proiettili.end(), (Proiettile*)mappa[arrivo.y][arrivo.x]));
                            rimuoviComponente(partenza);
                            rimuoviComponente(arrivo);
                            cancellaComponente(partenza);
                            stampaEffimera(arrivo);
                            break;
                        }
                        case TipoComponente::DIFENSORE: { // Collisione Proiettile nemico - Difensore
                            // Morte del Difensore
                            rimuoviComponente(partenza); // Rimozione del proiettile nemico
                            cancellaComponente(partenza);
                            exit(0);
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
    void Mappa::muoviProiettili() {
        std::vector<Proiettile*>::iterator it = proiettili.begin();
        Proiettile* proiettile = nullptr;
        Coordinate partenza, arrivo;
        for (; it < proiettili.end(); it++) {
            proiettile = *it;
            partenza = proiettile->getCoordinate();
            try {
                partenza.valida(altezza, larghezza);
            } catch (std::runtime_error& e) {
                // Il proiettile è uscito dalla mappa, quindi viene eliminato
                proiettili.erase(it);
                delete proiettile;
                continue;
            }
            arrivo = proiettile->calcolaProssimaPosizione();
            spostaComponente(partenza, arrivo);
            if (it == proiettili.end()) {
                break; // Il vettore potrebbe essersi accorciato durante spostaComponente()
            }
        }
    }
    void Mappa::generaProiettile(Coordinate& coordinate_, TipoProiettile tipoProiettile_, Direzione direzione_, int velocita_) {
        Coordinate coordinate = coordinate_ + direzioni[direzione_];
        try {
            coordinate.valida(altezza, larghezza);
        } catch (std::runtime_error& e) {
            // Il proiettile è uscito dalla mappa, quindi non viene generato
            return;
        }
        if (mappa[coordinate.y][coordinate.x] == nullptr) {
            if (tipoProiettile_ == TipoProiettile::P_NEMICO) {
                ProiettileNemico* proiettile = new ProiettileNemico(coordinate, direzione_, velocita_);
                proiettili.push_back(proiettile);
                immettiComponente(proiettile, coordinate);
                stampaComponente(coordinate);
            } else if (tipoProiettile_ == TipoProiettile::P_DIFENSORE) {
                ProiettileDifensore* proiettile = new ProiettileDifensore(coordinate, direzione_, velocita_, false);
                proiettili.push_back(proiettile);
                immettiComponente(proiettile, coordinate);
                stampaComponente(coordinate);
            }
        } else {
            if (tipoProiettile_ == TipoProiettile::P_NEMICO) {
                // Il proiettile nemico facciamo finta che non sia mai stato richiesto
            } else if (tipoProiettile_ == TipoProiettile::P_DIFENSORE) {
                // Il proiettile difensore sono costretto 
                switch (mappa[coordinate.y][coordinate.x]->getTipo()) {
                    case TipoComponente::TERRENO: {
                        Proiettile* proiettile = new ProiettileDifensore(coordinate, direzione_, velocita_, true);
                        proiettili.push_back(proiettile);
                        immettiComponente(proiettile, coordinate);
                        stampaComponente(coordinate);
                        break;
                    }
                    case TipoComponente::PROIETTILE_NEMICO: {
                        // Reindirizzamento del proiettile nemico
                        ((Proiettile*)mappa[coordinate.y][coordinate.x])->setDirezione(direzione_);
                        break;
                    }
                    default:
                        break;
                }
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
        for (int i = 0; i < larghezza + 2; i++) {
            std::cout << '@';
        }
        std::cout << '\n';
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
                        ANSI::reimposta();
                        std::cout << ' ';
                    }
                }
            }
            stileBordo.applica();
            std::cout << '@';
            std::cout << '\n';
        }
        for (int i = 0; i < larghezza + 2; i++) {
            std::cout << '@';
        }
        ANSI::reimposta();
        std::flush(std::cout);
    }
    ANSI::Stile stileDestinazione(
        ANSI::ColoreTesto::ROSSO,
        ANSI::ColoreSfondo::S_NERO,
        ANSI::Attributo::LAMPEGGIA
    );
};