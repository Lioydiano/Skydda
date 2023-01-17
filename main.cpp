#include <thread>
#include <chrono>
#include <future>
#include <random>
#include <conio.h>
#include "include/skydda/skydda.cpp"
// cd onedrive/documenti/github/skydda
// g++ main.cpp -o skydda -std=c++17 -Wall -O3


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


void stampaIntro() {
    std::cout << "\x1b]2;Skydda\x07"; // Questo comando cambia il titolo della finestra
    std::cout << "\t\t\t\t     \033[035;1mSKYDDA\033[0m\n";
    std::cout << "\t\t\t\033[3mCapture the goal to become the goat\033[0m\n\n";

    std::cout << "\t\t\t  \x1b[31;1mElissx \t\tFLAK-ZOSO\x1b[0m\n\n";

    std::cout << "\t\t\t- \033[035m 'v'\033[0m to try convalidating your path\n";
    std::cout << "\t\t\t- \033[035m 'p' 'r'\033[0m to pause/resume\n";
    std::cout << "\t\t\t- \033[035m 'w' 'a' 's' 'd'\033[0m to play\n";
    std::cout << "\t\t\t- \033[035m ^ > v <\033[0m (arrow keys) to shoot\n\n";

    std::cout << "\t\t\t\033[032m$\033[0m <---- this is you, the defender\n";
    std::cout << "\t\t\t\033[036m^\033[0m <---- this is an enemy bullet\n";
    std::cout << "\t\t\t\033[031mX\033[0m <---- this is the goal you need to reach\n\n";

    std::cout << "\t\t\tYou can hit your enemy with your bullets \033[035mv\033[0m\n";
    std::cout << "\t\tYou can make the bullets bounce, but we won't tell you how\n\n";

    std::cout << "\tRemember: to win you must connect the goal to the origin {0, 0} with a complete road!\033[0m\n";
    getch();
}


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
    skydda::Coordinate coordinate = difensore.getCoordinate() + skydda::direzioni[direzione];
    try {
        coordinate.valida(mappa.getAltezza(), mappa.getLarghezza());
    } catch (std::runtime_error& e) {
        return;
    }
    skydda::Coordinate vecchie = difensore.getCoordinate();
    mappa.spostaComponente(vecchie, coordinate);
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
    stampaIntro();
    srand(time(NULL));
    std::chrono::milliseconds durata(100);

    skydda::Mappa mappa(50, 20);

    int larghezza = generaIsola(mappa);
    mappa.immettiComponente(&difensore);
    mappa.stampa();
    skydda::Coordinate obiettivo = generaCoordinate(mappa); // Coordinate obbiettivo
    cursore.posiziona(obiettivo);
    skydda::stileDestinazione.applica();
    std::cout << "X";
    ANSI::reimposta();

    const skydda::Coordinate indicazioni_destinazione(8, 70); // Coordinate del terminale dove stampare le indicazioni sulla destinazione
    aggiornaCoordinateDifensore();
    cursore.posiziona(indicazioni_destinazione);
    ANSI::reimposta();
    std::cout << "Obiettivo: (" << obiettivo.y << ", " << obiettivo.x << ")";

    while (true) {
        std::future<Mossa> mossa = std::async(std::launch::async, leggiMossa);
        while (mossa.wait_for(durata) != std::future_status::ready) {
            mappa.muoviProiettili();
            if (rand() % 5 == 0) {
                skydda::Coordinate coord(20, rand() % 50);
                mappa.generaProiettile(
                    coord, skydda::TipoProiettile::P_NEMICO,
                    skydda::Direzione::NORD, 1
                );
            }
        }
        Mossa m = mossa.get();
        switch (m) {
            case MossaSinistra: {
                muoviDifensore(mappa, skydda::Direzione::OVEST);
                aggiornaCoordinateDifensore();
                break;
            }
            case MossaDestra: {
                muoviDifensore(mappa, skydda::Direzione::EST);
                aggiornaCoordinateDifensore();
                break;
            }
            case MossaSu: {
                muoviDifensore(mappa, skydda::Direzione::NORD);
                aggiornaCoordinateDifensore();
                break;
            }
            case MossaGiu: {
                muoviDifensore(mappa, skydda::Direzione::SUD);
                aggiornaCoordinateDifensore();
                break;
            }
            case SparaSinistra: case SparaDestra: case SparaSu: case SparaGiu: {
                skydda::Coordinate coordinate = difensore.getCoordinate();
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
                break;
            }
            case NessunaMossa:
                break;
            case Vinsten: { // L'utente pensa di aver vinto
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