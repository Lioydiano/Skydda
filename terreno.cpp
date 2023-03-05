#include "terreno.h"

namespace skydda {
    ANSI::Stile stileTerreno(ANSI::ColoreTesto::ROSSO, ANSI::ColoreSfondo::S_ROSSO, ANSI::Attributo::FLEBILE);
    Terreno::Terreno() : Componente('T', Coordinate(0, 0), stileTerreno, TipoComponente::TERRENO) {}
    Terreno::Terreno(Coordinate coordinate_) : Componente('T', coordinate_, stileTerreno, TipoComponente::TERRENO) {}
    Terreno::~Terreno() {}
}