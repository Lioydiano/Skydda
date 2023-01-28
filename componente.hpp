#ifndef COMPONENTE_hpp
	#define COMPONENTE_hpp
	#include <queue> // std::queue
	#include <vector> // std::vector, std::find, std::erase
	#include <unordered_map> // std::unordered_map
	#include "cursore.hpp"
	
	namespace skydda {
	    enum TipoComponente {
	        __IGNOTO__,
	        DIFENSORE,
	        PROIETTILE_DIFENSORE,
	        PROIETTILE_NEMICO,
	        TERRENO
	    };
	    enum Direzione { NORD, EST, SUD, OVEST };
	    enum TipoProiettile { P_DIFENSORE, P_NEMICO };
	    static std::unordered_map<Direzione, Coordinate> direzioni = { // Mappa che associa ogni direzione ad una coppia di coordinate, che indicano lo spostamento da effettuare
	        {NORD, Coordinate(-1, 0)},
	        {EST, Coordinate(0, 1)},
	        {SUD, Coordinate(1, 0)},
	        {OVEST, Coordinate(0, -1)}
	    };
	    static std::unordered_map<Direzione, char> direzioneCarattere = { // Mappa che associa ogni direzione ad un aspetto del proiettile, che indica la direzione di spostamento
	        {NORD, '^'},
	        {EST, '>'},
	        {SUD, 'v'},
	        {OVEST, '<'}
	    };
	    inline ANSI::Stile stileProiettileDifensore(ANSI::ColoreTesto::MAGENTA, ANSI::ColoreSfondo::S_ROSSO, ANSI::Attributo::LUMINOSO);
	    inline ANSI::Stile stileProiettileNemico(ANSI::ColoreTesto::CIANO, ANSI::ColoreSfondo::S_NERO, ANSI::Attributo::LUMINOSO);
	    inline ANSI::Stile stileNemico(ANSI::ColoreTesto::BLU, ANSI::ColoreSfondo::S_NERO, ANSI::Attributo::LUMINOSO);
	    inline ANSI::Stile stileDifensore(ANSI::ColoreTesto::VERDE, ANSI::ColoreSfondo::S_ROSSO, ANSI::Attributo::LUMINOSO);
	    inline ANSI::Stile stileEffimera(ANSI::ColoreTesto::BIANCO, ANSI::ColoreSfondo::S_NERO, ANSI::Attributo::FLEBILE);
	    inline ANSI::Stile stileTerreno(ANSI::ColoreTesto::ROSSO, ANSI::ColoreSfondo::S_ROSSO, ANSI::Attributo::FLEBILE);
	    inline ANSI::Stile stileBordo(ANSI::ColoreTesto::BIANCO, ANSI::ColoreSfondo::S_GIALLO, ANSI::Attributo::LUMINOSO);
	    inline ANSI::Stile stileDestinazione(ANSI::ColoreTesto::ROSSO, ANSI::ColoreSfondo::S_NERO, ANSI::Attributo::LAMPEGGIA);
	    inline std::unordered_map<TipoProiettile, ANSI::Stile> stiliProiettile = {
	        {TipoProiettile::P_DIFENSORE, stileProiettileDifensore},
	        {TipoProiettile::P_NEMICO, stileProiettileNemico}
	    };
	
		// Tutte le classi che ereditano da Componente, vanno elencate tramite forward-declaration per poterle usare l'una nell'altra
		class Difensore;
	    class Proiettile;
	    class ProiettileDifensore;
	    class ProiettileNemico;
	    class Terreno;
	    class Mappa;
	
	    // https://www.ibm.com/docs/en/zos/2.4.0?topic=only-abstract-classes-c (Classi astratte pure)
	    class Componente { // Classe astratta di base dalla quale ereditano tutti gli altri componenti
	    protected:
	        TipoComponente tipo; // Differenziare il tipo di componente
	        char carattere;
	        Coordinate coordinate;
	        ANSI::Stile stile;
	    
	    public:
	        Componente();
	        Componente(char, Coordinate, ANSI::Stile, TipoComponente);
	        virtual ~Componente() {} // Distruttore virtuale (https://github.com/FLAK-ZOSO/Sista/issues/2) (https://stackoverflow.com/questions/10338548/making-a-vector-of-instances-of-different-subclasses)
	
	        TipoComponente getTipo() const;
	        char getCarattere() const;
	        void setCarattere(char);
	        Coordinate getCoordinate() const;
	        void setCoordinate(Coordinate);
	        ANSI::Stile getStile() const;
	        void setStile(ANSI::Stile);
	
	        virtual void stampa();
	    };
	}
#endif