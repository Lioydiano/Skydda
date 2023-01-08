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
    NessunaMossa
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

void generaNemico(skydda::Mappa& mappa, int larghezza) {
    skydda::Coordinate coordinate;
    coordinate.x = larghezza + rand() % 10;
    coordinate.y = rand() % 20;
    int vita = rand() % 9 + 1;
    mappa.registraComponente(
        new skydda::Nemico(
            '0' + vita, coordinate, vita
        )
    );
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

int main() {
    srand(time(NULL));
    std::chrono::milliseconds durata(100);

    skydda::Mappa mappa(50, 20);

    int larghezza = generaIsola(mappa);
    generaNemico(mappa, larghezza);
    mappa.immettiComponente(&difensore);
    mappa.stampa();
    debug << "Mappa stampata" << std::endl;

    while (true) {
        std::future<Mossa> mossa = std::async(std::launch::async, leggiMossa);
        debug << "Funzione asincrona lanciata" << std::endl;
        while (mossa.wait_for(durata) != std::future_status::ready) {
            debug << "Mossa non pronta" << std::endl;
            mappa.muoviProiettili();
            debug << "\tProiettili mossi" << std::endl;
            // mappa.azionaNemici();
        }
        Mossa m = mossa.get();
        debug << "Mossa pronta: " << m << std::endl;
        switch (m) {
            case MossaSinistra: {
                debug << "Muovi difensore: sinistra" << std::endl;
                muoviDifensore(mappa, skydda::Direzione::OVEST);
                break;
            }
            case MossaDestra: {
                debug << "Muovi difensore: destra" << std::endl;
                muoviDifensore(mappa, skydda::Direzione::EST);
                break;
            }
            case MossaSu: {
                debug << "Muovi difensore: su" << std::endl;
                muoviDifensore(mappa, skydda::Direzione::NORD);
                break;
            }
            case MossaGiu: {
                debug << "Muovi difensore: giu" << std::endl;
                muoviDifensore(mappa, skydda::Direzione::SUD);
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
            default:
                break;
        }
    }

    std::this_thread::sleep_for(durata);
    return 0;
}