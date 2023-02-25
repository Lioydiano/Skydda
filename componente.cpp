#include "componente.hpp"

namespace skydda {
	// Mappa che associa ogni direzione ad una coppia di coordinate, che indicano lo spostamento da effettuare
    std::unordered_map<Direzione, Coordinate> direzioni = { 
        {NORD, Coordinate(-1, 0)},
        {EST, Coordinate(0, 1)},
        {SUD, Coordinate(1, 0)},
        {OVEST, Coordinate(0, -1)}
    };
	// Mappa che associa ogni direzione ad un aspetto del proiettile, che indica la direzione di spostamento
    std::unordered_map<Direzione, char> direzioneCarattere = { 
        {NORD, '^'},
        {EST, '>'},
        {SUD, 'v'},
        {OVEST, '<'}
    };
	/* Elenco degli stili per i vari tipi di componente */
    ANSI::Stile stileProiettileDifensore(ANSI::ColoreTesto::MAGENTA, ANSI::ColoreSfondo::S_ROSSO, ANSI::Attributo::LUMINOSO);
    ANSI::Stile stileProiettileNemico(ANSI::ColoreTesto::CIANO, ANSI::ColoreSfondo::S_NERO, ANSI::Attributo::LUMINOSO);
    ANSI::Stile stileNemico(ANSI::ColoreTesto::BLU, ANSI::ColoreSfondo::S_NERO, ANSI::Attributo::LUMINOSO);
    ANSI::Stile stileDifensore(ANSI::ColoreTesto::VERDE, ANSI::ColoreSfondo::S_ROSSO, ANSI::Attributo::LUMINOSO);
    ANSI::Stile stileEffimera(ANSI::ColoreTesto::BIANCO, ANSI::ColoreSfondo::S_NERO, ANSI::Attributo::FLEBILE);
    ANSI::Stile stileTerreno(ANSI::ColoreTesto::ROSSO, ANSI::ColoreSfondo::S_ROSSO, ANSI::Attributo::FLEBILE);
    ANSI::Stile stileBordo(ANSI::ColoreTesto::BIANCO, ANSI::ColoreSfondo::S_GIALLO, ANSI::Attributo::LUMINOSO);
    ANSI::Stile stileDestinazione(ANSI::ColoreTesto::ROSSO, ANSI::ColoreSfondo::S_NERO, ANSI::Attributo::LAMPEGGIA);
	// Mappa che associa ogni tipo di proiettile ad uno stile, che indica il colore e l'aspetto del proiettile, per evitare di dover fare un controllo ogni volta
	std::unordered_map<TipoProiettile, ANSI::Stile> stiliProiettile = {
        {TipoProiettile::P_DIFENSORE, stileProiettileDifensore},
        {TipoProiettile::P_NEMICO, stileProiettileNemico}
    };

    Componente::Componente() : carattere(), coordinate(), stile(), tipo(__IGNOTO__) {}
    Componente::Componente(char carattere_, Coordinate coordinata_, ANSI::Stile stile_, TipoComponente tipo_) : carattere(carattere_), coordinate(coordinata_), stile(stile_), tipo(tipo_) {}
    TipoComponente Componente::getTipo() const {
        return this->tipo;
    }
    char Componente::getCarattere() const {
        return this->carattere;
    }
    void Componente::setCarattere(char carattere_) {
        this->carattere = carattere_;
    }
    Coordinate Componente::getCoordinate() const {
        return this->coordinate;
    }
    void Componente::setCoordinate(Coordinate coordinate_) {
        this->coordinate = coordinate_;
    }
    ANSI::Stile Componente::getStile() const {
        return this->stile;
    }
    void Componente::setStile(ANSI::Stile stile_) {
        this->stile = stile_;
    }
    void Componente::stampa() {
        this->stile.applica();
        std::cout << this->carattere;
    }
}