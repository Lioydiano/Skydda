#include "terreno.hpp"

namespace skydda {
    Terreno::Terreno() : Componente(' ', Coordinate(0, 0), stileTerreno, TipoComponente::TERRENO) {}
    Terreno::Terreno(Coordinate coordinate_) : Componente(' ', coordinate_, stileTerreno, TipoComponente::TERRENO) {}
    Terreno::~Terreno() {}
}