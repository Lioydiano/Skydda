#include "proiettile.hpp"


namespace skydda {
	Proiettile::Proiettile() : Componente(direzioneCarattere[EST], Coordinate(0, 0), stileProiettileDifensore, TipoComponente::PROIETTILE_DIFENSORE), origine(TipoProiettile::P_DIFENSORE), direzione(EST), velocita(1) {}
    Proiettile::Proiettile(Coordinate coordinate_, TipoProiettile tipo_, Direzione direzione_, int velocita_) : Componente(direzioneCarattere[direzione_], coordinate_, stiliProiettile[tipo_], TipoComponente::PROIETTILE_DIFENSORE), origine(tipo_), direzione(direzione_), velocita(velocita_) {
        this->tipo = tipo_ == TipoProiettile::P_DIFENSORE ? TipoComponente::PROIETTILE_DIFENSORE : TipoComponente::PROIETTILE_NEMICO;
    }
    Proiettile::Proiettile(char carattere_, Coordinate coordinate_, TipoProiettile tipo_, Direzione direzione_, int velocita_) : Componente(carattere_, coordinate_, stiliProiettile[tipo_], TipoComponente::PROIETTILE_DIFENSORE), origine(tipo_), direzione(direzione_), velocita(velocita_) {
        this->tipo = tipo_ == TipoProiettile::P_DIFENSORE ? TipoComponente::PROIETTILE_DIFENSORE : TipoComponente::PROIETTILE_NEMICO;
    }
    Proiettile::~Proiettile() {}
    TipoProiettile Proiettile::getOrigine() const {
        return origine;
    }
    Direzione Proiettile::getDirezione() const {
        return direzione;
    }
    void Proiettile::setDirezione(Direzione direzione_) {
        direzione = direzione_;
        carattere = direzioneCarattere[direzione];
    }
    int Proiettile::getVelocita() const {
        return velocita;
    }
    Coordinate Proiettile::calcolaProssimaPosizione() const {
        return coordinate + direzioni[direzione] * velocita;
    }
}