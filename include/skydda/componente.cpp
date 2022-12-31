#pragma once
#include "componente.hpp"

namespace skydda {
    Componente::Componente() : carattere(), coordinate(), stile() {}
    Componente::Componente(char carattere_, Coordinate coordinata_, ANSI::Stile stile_) : carattere(carattere_), coordinate(coordinata_), stile(stile_) {}
}