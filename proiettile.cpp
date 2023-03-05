#include "proiettile.h"


namespace skydda {
    char _direzioneCarattere(Direzione direzione_) {
        // Mappa che associa ogni direzione ad un aspetto del proiettile, che indica la direzione di spostamento
	    std::unordered_map<Direzione, char> direzioneCarattere = { 
	        {NORD, '^'},
	        {EST, '>'},
	        {SUD, 'v'},
	        {OVEST, '<'}
	    };
        return direzioneCarattere[direzione_];
    }
    ANSI::Stile _stiliProiettile(TipoProiettile tipo_) {
        ANSI::Stile stileProiettileDifensore(
            ANSI::ColoreTesto::MAGENTA,
            ANSI::ColoreSfondo::S_ROSSO,
            ANSI::Attributo::LUMINOSO
        );
	    ANSI::Stile stileProiettileNemico(
            ANSI::ColoreTesto::CIANO,
            ANSI::ColoreSfondo::S_NERO,
            ANSI::Attributo::LUMINOSO
        );
        // Mappa che associa ogni tipo di proiettile ad uno stile, che indica il colore e l'aspetto del proiettile, per evitare di dover fare un controllo ogni volta
		std::unordered_map<TipoProiettile, ANSI::Stile> stiliProiettile = {
	        {TipoProiettile::P_DIFENSORE, stileProiettileDifensore},
	        {TipoProiettile::P_NEMICO, stileProiettileNemico}
	    };
        return stiliProiettile[tipo_];
    }
	Proiettile::Proiettile() : Componente('>', Coordinate(0, 0), _stiliProiettile(skydda::TipoProiettile::P_DIFENSORE), TipoComponente::PROIETTILE_DIFENSORE), origine(TipoProiettile::P_DIFENSORE), direzione(EST), velocita(1) {}
    Proiettile::Proiettile(Coordinate coordinate_, TipoProiettile tipo_, Direzione direzione_, int velocita_) : Componente(_direzioneCarattere(direzione_), coordinate_, _stiliProiettile(tipo_), TipoComponente::PROIETTILE_DIFENSORE), origine(tipo_), direzione(direzione_), velocita(velocita_) {
        this->tipo = tipo_ == TipoProiettile::P_DIFENSORE ? TipoComponente::PROIETTILE_DIFENSORE : TipoComponente::PROIETTILE_NEMICO;
    }
    Proiettile::Proiettile(char carattere_, Coordinate coordinate_, TipoProiettile tipo_, Direzione direzione_, int velocita_) : Componente(carattere_, coordinate_, _stiliProiettile(tipo_), TipoComponente::PROIETTILE_DIFENSORE), origine(tipo_), direzione(direzione_), velocita(velocita_) {
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
        carattere = _direzioneCarattere(direzione);
    }
    int Proiettile::getVelocita() const {
        return velocita;
    }
    Coordinate Proiettile::calcolaProssimaPosizione() const {
        // Mappa che associa ogni direzione ad una coppia di coordinate, che indicano lo spostamento da effettuare
	    std::unordered_map<Direzione, Coordinate> direzioni = { 
	        {NORD, Coordinate(-1, 0)},
	        {EST, Coordinate(0, 1)},
	        {SUD, Coordinate(1, 0)},
	        {OVEST, Coordinate(0, -1)}
	    };
        return coordinate + direzioni[direzione] * velocita;
    }
}