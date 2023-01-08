#include <thread>
#include <chrono>
#include <random>
#include <time.h>
#include "include/skydda/skydda.cpp"
// g++ main.cpp -o skydda -std=c++17 -Wall

std::ofstream evoluzione("evoluzione.txt", std::ios::out);

int main() {
    std::srand(time(NULL));
    skydda::pulisciSchermo();
    skydda::Mappa mappa(50, 20);
    skydda::Coordinate coordinate;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20 - i; j++) {
            coordinate.y = i;
            coordinate.x = j;
            mappa.immettiComponente(
                new skydda::Terreno(coordinate),
                coordinate
            );
        }
    }
    coordinate.y = 0;
    coordinate.x = 0;
    mappa.immettiComponente(
        new skydda::Difensore,
        coordinate
    );
    coordinate.y = 19;
    coordinate.x = 19;
    mappa.registraComponente(
        new skydda::Nemico(
            '3', coordinate, 3
        )
    );
    coordinate.y = 0;
    coordinate.x = 49;
    mappa.registraComponente(
        new skydda::Nemico(
            '1', coordinate, 1
        )
    );
    coordinate.y = 17;
    coordinate.x = 19;
    skydda::ProiettileNemico* pn = new skydda::ProiettileNemico(
        coordinate, skydda::OVEST, 1
    );
    mappa.registraComponente(pn);
    coordinate.y = 2;
    coordinate.x = 3;
    skydda::ProiettileDifensore* pd = new skydda::ProiettileDifensore(
        coordinate, skydda::SUD, 1
    );
    mappa.registraComponente(pd);
    coordinate.y = 2;
    coordinate.x = 4;
    skydda::ProiettileDifensore* pd2 = new skydda::ProiettileDifensore(
        coordinate, skydda::EST, 1
    );
    mappa.registraComponente(pd2);
    mappa.stampa();
    coordinate.y = 0;
    coordinate.x = 0;
    while (true) {
        if (rand() % 3 == 0) {
            int v = 1;
            coordinate.x = rand() % 4 + 1;
            mappa.generaProiettile(coordinate, skydda::P_DIFENSORE, skydda::EST, v);
            coordinate.x = 49 - v;
            mappa.generaProiettile(coordinate, skydda::P_NEMICO, skydda::OVEST, v);
        }
        mappa.muoviProiettili();
        for (int i = 0; i < 50; i++) {
            skydda::Coordinate c(0, i);
            if (mappa.getComponente(c) != nullptr) {
                evoluzione << mappa.getComponente(c)->getTipo();
            } else {
                evoluzione << "-";
            }
        }
        evoluzione << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cin.get();
}