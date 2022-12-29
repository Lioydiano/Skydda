#pragma once
#include "../sista/sista.hpp"


class Terrain: public sista::Pawn {
public:

    Terrain(sista::Coordinates coordinates_): sista::Pawn(' ', coordinates_, ANSI::Settings(ANSI::ForegroundColor::F_RED, ANSI::BackgroundColor::B_GREEN, ANSI::Attribute::REVERSE)) {}
    ~Terrain() {}
};