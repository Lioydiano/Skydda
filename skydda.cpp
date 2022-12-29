// g++ skydda.cpp -o skydda -std=c++17 -Wall
#include "include/skydda/skydda.hpp"
#include <thread>


int main() {
    sista::SwappableField field(50, 20);
    sista::Border border(
        '@', ANSI::Settings(
            ANSI::ForegroundColor::F_WHITE,
            ANSI::BackgroundColor::B_YELLOW,
            ANSI::Attribute::BRIGHT
        )
    );
    std::vector<sista::Pawn*> pawns;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10 - i; j++) {
            pawns.push_back(new Terrain(sista::Coordinates(j, i)));
            field.addPawn(pawns.back());
        }
    }
    field.print(border);
    system("pause>nul");
}