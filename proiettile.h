#ifndef PROIETTILE_hpp
	#define PROIETTILE_hpp
	#include "terreno.h"
	
	
	namespace skydda {
		class Proiettile : public Componente {
		    protected:
		        TipoProiettile origine; // Differenziare l'origine
		        Direzione direzione;
		        int velocita;
		
		    public:
		        Proiettile();
		        Proiettile(Coordinate, TipoProiettile, Direzione, int);
		        Proiettile(char, Coordinate, TipoProiettile, Direzione, int);
		        ~Proiettile() override;
		
		        TipoProiettile getOrigine() const;
		        Direzione getDirezione() const;
		        void setDirezione(Direzione);
		        int getVelocita() const;
		
		        Coordinate calcolaProssimaPosizione() const; // Calcola la prossima posizione del proiettile
		};
	}
#endif