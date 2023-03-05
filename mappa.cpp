#include "mappa.h"
#include <algorithm>


namespace skydda {
    ANSI::Stile stileEffimera(ANSI::ColoreTesto::BIANCO, ANSI::ColoreSfondo::S_NERO, ANSI::Attributo::FLEBILE);
	void stampaEffimera(Coordinate& coordinate) {
        std::cout << CSI << coordinate.y + 2 << ";" << coordinate.x + 2 << "H";
        stileEffimera.applica();
        std::cout << "*";
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
        try { // Controllo che le coordinate siano valide
            arrivo.valida(altezza, larghezza);
        } catch (std::runtime_error& e) { // Se non lo sono, lancia un'eccezione, che verrà gestita dal ramo catch
            switch (mappa[partenza.y][partenza.x]->getTipo()) { // Controllo quale tipo di Componente è andata a sbattere contro un muro
                case TipoComponente::PROIETTILE_DIFENSORE: { // Se è un ProiettileDifensore, lo elimino e lo sostituisco con un Terreno (se sopraTerreno è true)
                    proiettili.erase(std::find(proiettili.begin(), proiettili.end(), (Proiettile*)mappa[partenza.y][partenza.x])); // Rimuovo il ProiettileDifensore* dalla lista dei proiettili
                    if (((ProiettileDifensore*)mappa[partenza.y][partenza.x])->getSopraTerreno()) { // Se sopraTerreno è true, sostituisco il ProiettileDifensore con un Terreno
                        immettiComponente(new Terreno(partenza), partenza); // Creo un nuovo Terreno e lo immetto nella mappa
                        stampaComponente(partenza); // Stampo il Terreno nella mappa
                    } else {
                        rimuoviComponente(partenza); // Altrimenti, semplicemente lo elimino
                        cancellaComponente(partenza); // Cancello il ProiettileDifensore dalla mappa
                    }
                    break;
                }
                case TipoComponente::PROIETTILE_NEMICO: { // Se è un ProiettileNemico, lo elimino e basta, non c'è bisogno di sostituirlo con un Terreno
                    proiettili.erase(std::find(proiettili.begin(), proiettili.end(), (Proiettile*)mappa[partenza.y][partenza.x])); // Rimuovo il ProiettileNemico* dalla lista dei proiettili
                    rimuoviComponente(partenza);
                    cancellaComponente(partenza);
                    break;
                }
                case TipoComponente::DIFENSORE: { // Se è un Difensore che prova ad andare fuori dalla mappa, gli impedisco di farlo ignorando la sua richiesta
                    break;
                }
                default:
                    break;
            }
            return; // Ritorno, in modo da non eseguire il resto del metodo
        }
        // Se le coordinate invece sono valide...
        if (mappa[arrivo.y][arrivo.x] == nullptr) { // ...e la casella di arrivo è vuota, sposto il Componente
            Componente* componente = mappa[partenza.y][partenza.x]; // Salvo il Componente* nella variabile componente
            mappa[partenza.y][partenza.x] = nullptr; // Svuoto la casella di partenza della mappa
            componente->setCoordinate(arrivo); // Aggiorno le coordinate del Componente (deve sapere dove si trova)
            mappa[arrivo.y][arrivo.x] = componente; // Aggiorno la casella di arrivo della mappa inserendo il Componente*
            if (mappa[arrivo.y][arrivo.x]->getTipo() == TipoComponente::PROIETTILE_DIFENSORE) { // Se il Componente* è un ProiettileDifensore...
                if (((ProiettileDifensore*)mappa[arrivo.y][arrivo.x])->getSopraTerreno()) { // ...e sopraTerreno è true, sostituisco il ProiettileDifensore con un Terreno
                    immettiComponente(new Terreno(partenza), partenza); // Creo un nuovo Terreno e lo immetto nella mappa
                    ((ProiettileDifensore*)mappa[arrivo.y][arrivo.x])->setSopraTerreno(false); // Imposto sopraTerreno a false (perché la casella di arrivo era vuota e quindi non c'è più un Terreno sotto il ProiettileDifensore)
                    stampaComponente(partenza); // Stampo il contenuto della casella di arrivo, che ora è il ProiettileDifensore
                } else {
                    cancellaComponente(partenza); // Altrimenti, semplicemente cancello il contenuto della casella di partenza
                }
            } else {
                cancellaComponente(partenza); // Se il Componente* non è un ProiettileDifensore*, semplicemente cancello il contenuto della casella di partenza
            }
            stampaComponente(arrivo); // Stampo il contenuto della casella di arrivo
        } else { // Se invece la casella di arrivo non è vuota, ci sarà una collisione...
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
        std::vector<Proiettile*>::iterator it = proiettili.begin(); // Iteratore per il vettore dei proiettili (parte dall'inizio)
        Proiettile* proiettile = nullptr; // inizializzo un puntatore a Proiettile
        Coordinate partenza, arrivo; // Coordinate di partenza e arrivo del proiettile
        for (; it < proiettili.end(); it++) { // Itero su tutti i proiettili (con gli iteratori, fino a proiettili.end())
            proiettile = *it; // Assegno il puntatore al proiettile corrente
            partenza = proiettile->getCoordinate(); // Ottengo le coordinate del proiettile corrente
            try {
                partenza.valida(altezza, larghezza);
            } catch (std::runtime_error& e) {
                // Il proiettile è uscito dalla mappa, quindi viene eliminato
                proiettili.erase(it);
                delete proiettile; // Deallocazione della memoria (dall'heap https://cdn.discordapp.com/attachments/874752056626389033/1069290702871203950/image.png) del proiettile
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
        // Mappa che associa ogni direzione ad una coppia di coordinate, che indicano lo spostamento da effettuare
	    std::unordered_map<Direzione, Coordinate> direzioni = { 
	        {NORD, Coordinate(-1, 0)},
	        {EST, Coordinate(0, 1)},
	        {SUD, Coordinate(1, 0)},
	        {OVEST, Coordinate(0, -1)}
	    };
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
    void Mappa::stampa() const {
        pulisciSchermo();
        ANSI::Stile stileBordo(ANSI::ColoreTesto::BIANCO, ANSI::ColoreSfondo::S_GIALLO, ANSI::Attributo::LUMINOSO);
        stileBordo.applica();
        for (int i = 0; i < larghezza + 2; i++) { // Stampa la prima riga di bordo
            std::cout << '@';
        }
        std::cout << '\n';
        for (int i = 0; i < altezza; i++) {
            bool spazioPrecedente = false; // Serve per evitare di ripristinare lo stile ANSI ogni volta che si stampa uno spazio
            std::cout << '@';
            for (int j = 0; j < larghezza; j++) {
                if (mappa[i][j] != nullptr) { // Se la cella non è vuota
                    spazioPrecedente = false; // Significa che ora sarà applicato dello stile, e la prossima volta sarà necessario ripristinarlo
                    mappa[i][j]->stampa(); // Stampa il Componente (il metodo stampa() è virtuale e quindi sovrascritto tramite overriding dalle classi figlie)
                } else {
                    if (spazioPrecedente) { // Se il carattere precedente era uno spazio, non è necessario ripristinare lo stile ANSI
                        std::cout << ' '; // Stampa uno spazio (non è necessario reimpostare lo stile ANSI)
                    } else { // Altrimenti...
                        spazioPrecedente = true; // ...significa che era stato applicato uno stile...
                        ANSI::reimposta(); // ...quindi è necessario reimpostarlo
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
}