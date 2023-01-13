#include <thread>
#include <chrono>
#include <future>
#include <random>
#include <conio.h>
#include "include/skydda/skydda.cpp"
// cd onedrive/documenti/github/skydda
// g++ main.cpp -o skydda -std=c++17 -Wall


enum Mossa {
    MossaSinistra,
    MossaDestra,
    MossaSu,
    MossaGiu,
    SparaSinistra,
    SparaDestra,
    SparaSu,
    SparaGiu,
    NessunaMossa,
    Vinsten
};


Mossa leggiMossa() {
    char carattere = getch();
    if (carattere == -32) {
        carattere = getch(); // Eludi la [ che segue \033
        switch (carattere) {
            case 72:
                return SparaSu;
            case 80:
                return SparaGiu;
            case 75:
                return SparaSinistra;
            case 77:
                return SparaDestra;
            default:
                break;
        }
    }
    switch (carattere) {
        case 'w': case 'W':
            return MossaSu;
        case 's': case 'S':
            return MossaGiu;
        case 'd': case 'D':
            return MossaDestra;
        case 'a': case 'A':
            return MossaSinistra;
        case 'v': case 'V':
            return Vinsten;
        default:
            break;
    }
    return NessunaMossa;
}

int generaIsola(skydda::Mappa& mappa) {
    int larghezza = 15 + rand() % 5;
    skydda::Coordinate coordinate;
    for (int i = 0; i < larghezza; i++) {
        for (int j = 0; j < larghezza - i; j++) {
            coordinate.y = j;
            coordinate.x = i;
            mappa.immettiComponente(
                new skydda::Terreno(
                    coordinate
                ), coordinate
            );
        }
    }
    return larghezza;
}

skydda::Difensore difensore;

void muoviDifensore(skydda::Mappa& mappa, skydda::Direzione direzione) {
    debug << "\tMuovi difensore in direzione " << direzione << std::endl;
    skydda::Coordinate coordinate = difensore.getCoordinate() + skydda::direzioni[direzione];
    debug << "\tCoordinate: (" << coordinate.x << ", " << coordinate.y << ")" << std::endl;
    try {
        coordinate.valida(mappa.getAltezza(), mappa.getLarghezza());
    } catch (std::runtime_error& e) {
        return;
    }
    debug << "\tCoordinate valide" << std::endl;
    skydda::Coordinate vecchie = difensore.getCoordinate();
    debug << "\tVecchie coordinate: (" << vecchie.x << ", " << vecchie.y << ")" << std::endl;
    mappa.spostaComponente(vecchie, coordinate);
    debug << "\tComponente spostato" << std::endl;
}
skydda::Cursore cursore; // Cursore ausiliario per stampare le indicazioni
const skydda::Coordinate indicazioni_difensore(10, 70); // Coordinate del terminale dove stampare le indicazioni sul difensore
void aggiornaCoordinateDifensore() {
    cursore.posiziona(indicazioni_difensore);
    ANSI::reimposta();
    std::cout << "Difensore: (" << difensore.getCoordinate().y << ", " << difensore.getCoordinate().x << ")   ";
}

skydda::Coordinate generaCoordinate(skydda::Mappa& mappa) {
    skydda::Coordinate coordinate;
    while (true) {
        coordinate.x = rand() % mappa.getLarghezza();
        coordinate.y = rand() % mappa.getAltezza();
        if (mappa.getComponente(coordinate) == nullptr)
            break;
    }
    return coordinate;
}

int main() {
    srand(time(NULL));
    std::chrono::milliseconds durata(100);

    skydda::Mappa mappa(50, 20);
    skydda::Coordinate obiettivo = generaCoordinate(mappa); // Coordinate obbiettivo

    int larghezza = generaIsola(mappa);
    mappa.immettiComponente(&difensore);
    mappa.stampa();
    debug << "Mappa stampata" << std::endl;

    const skydda::Coordinate indicazioni_destinazione(8, 70); // Coordinate del terminale dove stampare le indicazioni sulla destinazione
    aggiornaCoordinateDifensore();
    cursore.posiziona(indicazioni_destinazione);
    ANSI::reimposta();
    std::cout << "Obiettivo: (" << obiettivo.y << ", " << obiettivo.x << ")";

    while (true) {
        std::future<Mossa> mossa = std::async(std::launch::async, leggiMossa);
        debug << "Funzione asincrona lanciata" << std::endl;
        while (mossa.wait_for(durata) != std::future_status::ready) {
            debug << "Mossa non pronta" << std::endl;
            mappa.muoviProiettili();
            debug << "\tProiettili mossi" << std::endl;
            if (rand() % 5 == 0) {
                skydda::Coordinate coord(20, rand() % 50);
                mappa.generaProiettile(
                    coord, skydda::TipoProiettile::P_NEMICO,
                    skydda::Direzione::NORD, 1
                );
            }
        }
        Mossa m = mossa.get();
        debug << "Mossa pronta: " << m << std::endl;
        switch (m) {
            case MossaSinistra: {
                debug << "Muovi difensore: sinistra" << std::endl;
                muoviDifensore(mappa, skydda::Direzione::OVEST);
                aggiornaCoordinateDifensore();
                break;
            }
            case MossaDestra: {
                debug << "Muovi difensore: destra" << std::endl;
                muoviDifensore(mappa, skydda::Direzione::EST);
                aggiornaCoordinateDifensore();
                break;
            }
            case MossaSu: {
                debug << "Muovi difensore: su" << std::endl;
                muoviDifensore(mappa, skydda::Direzione::NORD);
                aggiornaCoordinateDifensore();
                break;
            }
            case MossaGiu: {
                debug << "Muovi difensore: giu" << std::endl;
                muoviDifensore(mappa, skydda::Direzione::SUD);
                aggiornaCoordinateDifensore();
                break;
            }
            case SparaSinistra: case SparaDestra: case SparaSu: case SparaGiu: {
                debug << "Spara difensore" << std::endl;
                skydda::Coordinate coordinate = difensore.getCoordinate();
                debug << "\tCoordinate: (" << coordinate.x << ", " << coordinate.y << ")" << std::endl;
                switch (m) {
                    case SparaSinistra:
                        mappa.generaProiettile(
                            coordinate, skydda::TipoProiettile::P_DIFENSORE, 
                            skydda::Direzione::OVEST, 1
                        );
                        break;
                    case SparaDestra:
                        mappa.generaProiettile(
                            coordinate, skydda::TipoProiettile::P_DIFENSORE, 
                            skydda::Direzione::EST, 1
                        );
                        break;
                    case SparaSu:
                        mappa.generaProiettile(
                            coordinate, skydda::TipoProiettile::P_DIFENSORE, 
                            skydda::Direzione::NORD, 1
                        );
                        break;
                    case SparaGiu:
                        mappa.generaProiettile(
                            coordinate, skydda::TipoProiettile::P_DIFENSORE, 
                            skydda::Direzione::SUD, 1
                        );
                        break;
                    default:
                        break;
                }
                debug << "\tProiettile generato" << std::endl;
                break;
            }
            case NessunaMossa:
                debug << "Nessuna mossa" << std::endl;
                break;
            case Vinsten: { // L'utente pensa di aver vinto
                debug << "Vinsten" << std::endl;
                skydda::Coordinate coordinate_difensore = difensore.getCoordinate();
                mappa.immettiComponente(new skydda::Terreno(coordinate_difensore), coordinate_difensore);
                skydda::Coordinate origine_(0, 0);
                skydda::Componente* origine = mappa.getComponente(origine_);
                skydda::Componente* componente = mappa.getComponente(obiettivo);
                if (componente != nullptr && origine != nullptr) { // Se l'obiettivo non è vuoto...
                    if (componente->getTipo() == skydda::TipoComponente::TERRENO && origine->getTipo() == skydda::TipoComponente::TERRENO) {
                        // BFS per trovare eventuali connessioni tra obiettivo e origine
                        std::queue<skydda::Coordinate> coda;
                        std::vector<std::vector<bool>> visitati(mappa.getAltezza());
                        for (int i=0; i<mappa.getAltezza(); i++) { // Per ogni riga
                            visitati[i].resize(mappa.getLarghezza(), false); // La allargo e inizializzo a false
                        }
                        coda.push(obiettivo); // Parto dall'obiettivo, e tento di raggiungere l'origine
                        skydda::Coordinate cima;
                        skydda::Coordinate coordinate_vicino;
                        while (!coda.empty()) {
                            cima = coda.front(); // Prendi l'ultimo della coda
                            coda.pop(); // Elimina l'ultimo della coda
                            visitati[cima.y][cima.x] = true; // Segno come visitato
                            if (cima.y == 0 && cima.x == 0)
                                break;

                            for (int i=0; i<4; i++) { // Itero sulle possibili direzioni
                                coordinate_vicino = cima + skydda::direzioni[(skydda::Direzione)i]; // Guardiamo il blocco in quella direzione
                                try {
                                    coordinate_vicino.valida(mappa.getAltezza(), mappa.getLarghezza());
                                    if (visitati[coordinate_vicino.y][coordinate_vicino.x]) // Se è già stato visitato, non lo considero
                                        continue;
                                    skydda::Componente* vicino = mappa.getComponente(coordinate_vicino);
                                    if (vicino != nullptr) {
                                        if (vicino->getTipo() == skydda::TipoComponente::TERRENO) {
                                            coda.push(coordinate_vicino); // Richiedo che venga esplorata la zona del vicino
                                        }
                                    }
                                } catch (std::runtime_error& e) {
                                    continue;
                                }
                            }
                        }
                        if (visitati[0][0]) { // Abbiamo visitato l'origine
                            skydda::Coordinate c_(22, 0);
                            cursore.posiziona(c_);
                            ANSI::reimposta();
                            std::cout << "Hai vinto!";
                            std::cin.get();
                            return 0;
                        } else {
                            return 0;
                        }
                    } else {
                        skydda::Coordinate c_(22, 0);
                        cursore.posiziona(c_);
                        ANSI::reimposta();
                        std::cout << "Hai perso!";
                        std::cin.get();
                        return 0;
                    }
                } else {
                    skydda::Coordinate c_(22, 0);
                    cursore.posiziona(c_);
                    ANSI::reimposta();
                    std::cout << "Hai perso!";
                    std::cin.get();
                    return 0;
                }
                return 0;
            }
            default:
                break;
        }
    }

    std::this_thread::sleep_for(durata);
    return 0;
}