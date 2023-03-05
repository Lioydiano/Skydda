#ifndef COMPONENTE_hpp
	#define COMPONENTE_hpp
	#include <queue> // std::queue [per la BFS]
	#include <vector> // std::vector, std::find, std::erase
	#include <unordered_map> // std::unordered_map
	#include "cursore.h"
	
	namespace skydda {
		// TipoComponente serve a distinguere i vari tipi di componenti, in modo da poterli trattare in modo diverso, senza dover fare un controllo sul tipo di componente ogni volta
	    enum TipoComponente {
	        __IGNOTO__,
	        DIFENSORE,
	        PROIETTILE_DIFENSORE,
	        PROIETTILE_NEMICO,
	        TERRENO
	    };
	    enum Direzione { NORD, EST, SUD, OVEST }; // Serve a distinguere le varie direzioni, in modo da non dover ogni volta ricordare che 0 = NORD, 1 = EST, 2 = SUD, 3 = OVEST
	    enum TipoProiettile { P_DIFENSORE, P_NEMICO }; // Serve a distinguere i vari tipi di proiettile, in modo da poterli trattare in modo diverso, senza dover fare un controllo sul tipo di proiettile ogni volta

		/* Elenco degli stili per i vari tipi di componente */
		// ANSI::Stile stileProiettileNemico(ANSI::ColoreTesto::CIANO, ANSI::ColoreSfondo::S_NERO, ANSI::Attributo::LUMINOSO);
	    // ANSI::Stile stileNemico(ANSI::ColoreTesto::BLU, ANSI::ColoreSfondo::S_NERO, ANSI::Attributo::LUMINOSO);
	    // ANSI::Stile stileDifensore(ANSI::ColoreTesto::VERDE, ANSI::ColoreSfondo::S_ROSSO, ANSI::Attributo::LUMINOSO);
	    // ANSI::Stile stileEffimera(ANSI::ColoreTesto::BIANCO, ANSI::ColoreSfondo::S_NERO, ANSI::Attributo::FLEBILE);
	    // ANSI::Stile stileTerreno(ANSI::ColoreTesto::ROSSO, ANSI::ColoreSfondo::S_ROSSO, ANSI::Attributo::FLEBILE);
	    // ANSI::Stile stileBordo(ANSI::ColoreTesto::BIANCO, ANSI::ColoreSfondo::S_GIALLO, ANSI::Attributo::LUMINOSO);
	    // ANSI::Stile stileDestinazione(ANSI::ColoreTesto::ROSSO, ANSI::ColoreSfondo::S_NERO, ANSI::Attributo::LAMPEGGIA);	

		// Tutte le classi che ereditano da Componente, vanno elencate tramite forward-declaration per poterle usare l'una nell'altra
		class Difensore;
	    class Proiettile;
	    class ProiettileDifensore;
	    class ProiettileNemico;
	    class Terreno;
	    class Mappa;

		// Classe base dalla quale ereditano tutti gli altri componenti del gioco
	    class Componente {
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