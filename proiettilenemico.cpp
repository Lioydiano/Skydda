#include "proiettilenemico.h"

namespace skydda {
    ProiettileNemico::ProiettileNemico() : Proiettile() {}
    ProiettileNemico::ProiettileNemico(Coordinate coordinate_, Direzione direzione_, int velocita_) : Proiettile(coordinate_, TipoProiettile::P_NEMICO, direzione_, velocita_) {}
    ProiettileNemico::ProiettileNemico(char carattere_, Coordinate coordinate_, Direzione direzione_, int velocita_) : Proiettile(carattere_, coordinate_, TipoProiettile::P_NEMICO, direzione_, velocita_) {}
    ProiettileNemico::~ProiettileNemico() {}
}