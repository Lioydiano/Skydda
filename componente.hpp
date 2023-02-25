#ifndef COMPONENTE_hpp
	#define COMPONENTE_hpp
	#include <queue> // std::queue [per la BFS]
	#include <vector> // std::vector, std::find, std::erase
	#include <unordered_map> // std::unordered_map
	#include "cursore.hpp"
	
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