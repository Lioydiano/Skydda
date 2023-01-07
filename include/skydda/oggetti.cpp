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
    int Proiettile::getVelocita() const {
        return velocita;
    }
    Coordinate Proiettile::calcolaProssimaPosizione() const {
        debug << "Proiettile::calcolaProssimaPosizione()" << std::endl;
        debug << "coordinate: (" << coordinate.y << ", " << coordinate.x << ")" << std::endl;
        debug << "spostamento: (" << direzioni[direzione].y << ", " << direzioni[direzione].x << ")" << std::endl;
        return coordinate + direzioni[direzione] * velocita;
    }

    ProiettileDifensore::ProiettileDifensore() : Proiettile() {}
    ProiettileDifensore::ProiettileDifensore(Coordinate coordinate_, Direzione direzione_, int velocita_) : Proiettile(coordinate_, TipoProiettile::P_DIFENSORE, direzione_, velocita_), sopraTerreno(true) {}
    ProiettileDifensore::ProiettileDifensore(char carattere_, Coordinate coordinate_, Direzione direzione_, int velocita_) : Proiettile(carattere_, coordinate_, TipoProiettile::P_DIFENSORE, direzione_, velocita_), sopraTerreno(true) {}
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
    Effimera::Effimera() : Componente(' ', Coordinate(0, 0), stileEffimera, TipoComponente::EFFIMERA) {}
    Effimera::Effimera(Coordinate coordinate_) : Componente(' ', coordinate_, stileEffimera, TipoComponente::EFFIMERA) {}
    Effimera::~Effimera() {}
    void Effimera::stampa() {
        stile.applica();
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
    void Mappa::registraComponente(Effimera* effimera) {
        effimere.push(effimera);
        immettiComponente(effimera);
    }
    void Mappa::registraComponente(Proiettile* proiettile) {
        proiettili.push_back(proiettile);
        immettiComponente(proiettile);
    }
    void Mappa::registraComponente(Nemico* nemico) {
        nemici.push_back(nemico);
        immettiComponente(nemico);
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
        debug << "Sposto " << mappa[partenza.y][partenza.x]->getTipo() << " da (" << partenza.y << ", " << partenza.x << ") a (" << arrivo.y << ", " << arrivo.x << ")" << std::endl;
        try {
            arrivo.valida(altezza, larghezza);
        } catch (std::runtime_error& e) {
            switch (mappa[partenza.y][partenza.x]->getTipo()) {
                case TipoComponente::PROIETTILE_DIFENSORE: case TipoComponente::PROIETTILE_NEMICO: {
                    debug << "Rimuovo proiettile" << std::endl;
                    proiettili.erase(std::find(proiettili.begin(), proiettili.end(), mappa[partenza.y][partenza.x]));
                    rimuoviComponente(partenza);
                    cancellaComponente(partenza);
                    break;
                }
                case TipoComponente::NEMICO: case TipoComponente::DIFENSORE: {
                    break;
                }
            }
        }
        if (mappa[arrivo.y][arrivo.x] == nullptr) {
            mappa[arrivo.y][arrivo.x] = mappa[partenza.y][partenza.x];
            mappa[partenza.y][partenza.x] = nullptr;
            mappa[arrivo.y][arrivo.x]->setCoordinate(arrivo);
            cancellaComponente(partenza);
            if (mappa[arrivo.y][arrivo.x]->getTipo() == TipoComponente::PROIETTILE_DIFENSORE) {
                if (((ProiettileDifensore*)mappa[arrivo.y][arrivo.x])->getSopraTerreno()) {
                    immettiComponente(new Terreno(partenza), partenza);
                    ((ProiettileDifensore*)mappa[arrivo.y][arrivo.x])->setSopraTerreno(false);
                }
                stampaComponente(partenza);
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
                            ProiettileDifensore* proiettile = (ProiettileDifensore*)mappa[partenza.y][partenza.x];
                            if (proiettile->getSopraTerreno()) {
                                // Il proiettile si trova sull'isola, quindi sul Terreno che va ripristinato
                                immettiComponente(new Terreno(partenza), partenza);
                            }
                            proiettili.erase(
                                std::find_if(
                                    proiettili.begin(),
                                    proiettili.end(),
                                    [partenza, arrivo](Proiettile* p) {
                                        return (
                                            p->getCoordinate() == partenza
                                            || p->getCoordinate() == arrivo
                                        );
                                    }
                                )
                            );
                            delete proiettile; // Deallocazione della memoria del proiettile difensore
                            delete mappa[arrivo.y][arrivo.x]; // Deallocazione della memoria del proiettile nemico
                            immettiComponente(new Effimera(arrivo), arrivo);
                            effimere.push((Effimera*)mappa[arrivo.y][arrivo.x]);
                            stampaComponente(arrivo);
                            stampaComponente(partenza);
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
                            proiettili.erase(
                                std::find_if(
                                    proiettili.begin(),
                                    proiettili.end(),
                                    [&](Proiettile* p) {
                                        return p->getCoordinate() == partenza;
                                    }
                                )
                            );
                            delete mappa[partenza.y][partenza.x]; // Deallocazione della memoria del proiettile nemico
                            mappa[partenza.y][partenza.x] = nullptr;
                            immettiComponente(new Effimera(arrivo), arrivo);
                            effimere.push((Effimera*)mappa[arrivo.y][arrivo.x]);
                            cancellaComponente(partenza);
                            stampaComponente(arrivo);
                            break;
                        }
                        case TipoComponente::PROIETTILE_DIFENSORE: { // Collisione Proiettile nemico - Proiettile difensore
                            // Distruzione dei due proiettili e creazione dell'effimera
                            delete mappa[arrivo.y][arrivo.x]; // Deallocazione della memoria del proiettile difensore
                            proiettili.erase(
                                std::find_if(
                                    proiettili.begin(),
                                    proiettili.end(),
                                    [&](Proiettile* p) {
                                        return p->getCoordinate() == partenza;
                                    }
                                )
                            );
                            delete mappa[partenza.y][partenza.x]; // Deallocazione della memoria del proiettile nemico
                            immettiComponente(new Effimera(arrivo), arrivo);
                            effimere.push((Effimera*)mappa[arrivo.y][arrivo.x]);
                            stampaComponente(arrivo);
                            cancellaComponente(partenza);
                            break;
                        }
                        case TipoComponente::NEMICO: { // Collisione Proiettile nemico - Nemico
                            // Incremento del Nemico
                            proiettili.erase(
                                std::find_if(
                                    proiettili.begin(),
                                    proiettili.end(),
                                    [&](Proiettile* p) {
                                        return p->getCoordinate() == partenza;
                                    }
                                )
                            );
                            delete mappa[partenza.y][partenza.x]; // Deallocazione della memoria del proiettile nemico
                            mappa[partenza.y][partenza.x] = nullptr;
                            Nemico* nemico = (Nemico*)mappa[arrivo.y][arrivo.x];
                            nemico->setVita(std::max(nemico->getVita() + 1, 9));
                            stampaComponente(arrivo);
                            cancellaComponente(partenza);
                            break;
                        }
                        case TipoComponente::DIFENSORE: { // Collisione Proiettile nemico - Difensore
                            // Morte del Difensore
                            delete mappa[partenza.y][partenza.x]; // Deallocazione della memoria del proiettile nemico
                            mappa[partenza.y][partenza.x] = nullptr;
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
        for (; it != proiettili.end(); it++) {
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
        }
    }
    void Mappa::rimuoviEffimere() {
        std::queue<Effimera*> coda;
        Coordinate coordinate;
        while (!effimere.empty()) {
            Effimera* effimera = effimere.front();
            effimere.pop();
            coordinate = effimera->getCoordinate();
            cancellaComponente(coordinate);
            delete effimera;
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
};