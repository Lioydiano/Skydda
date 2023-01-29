#include "proiettiledifensore.hpp"

namespace skydda {
    ProiettileDifensore::ProiettileDifensore() : Proiettile() {}
    ProiettileDifensore::ProiettileDifensore(Coordinate coordinate_, Direzione direzione_, int velocita_, bool sopraTerreno_=true) : Proiettile(coordinate_, TipoProiettile::P_DIFENSORE, direzione_, velocita_), sopraTerreno(sopraTerreno_) {
        // Se sopraTerreno è true, il colore di sfondo è rosso, altrimenti è nero
        stile.coloreSfondo = !sopraTerreno ? ANSI::ColoreSfondo::S_NERO : ANSI::ColoreSfondo::S_ROSSO;
    }
    ProiettileDifensore::ProiettileDifensore(char carattere_, Coordinate coordinate_, Direzione direzione_, int velocita_, bool sopraTerreno_=true) : Proiettile(carattere_, coordinate_, TipoProiettile::P_DIFENSORE, direzione_, velocita_), sopraTerreno(sopraTerreno_) {
        // Se sopraTerreno è true, il colore di sfondo è rosso, altrimenti è nero
        stile.coloreSfondo = !sopraTerreno ? ANSI::ColoreSfondo::S_NERO : ANSI::ColoreSfondo::S_ROSSO;
    }
    ProiettileDifensore::~ProiettileDifensore() {}
    bool ProiettileDifensore::getSopraTerreno() const {
        return sopraTerreno;
    }
    void ProiettileDifensore::setSopraTerreno(bool sopraTerreno_) {
        sopraTerreno = sopraTerreno_; // Quando viene modificato il valore di sopraTerreno, viene modificato anche il colore di sfondo
        stile.coloreSfondo = !sopraTerreno ? ANSI::ColoreSfondo::S_NERO : ANSI::ColoreSfondo::S_ROSSO;
    }
}