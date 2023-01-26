#ifndef PROIETTILEDIFENSORE_hpp
	#define PROIETTILEDIFENSORE_hpp
	#include "proiettile.hpp"
	
	namespace skydda {
		class ProiettileDifensore : public Proiettile {
	    private:
	        bool sopraTerreno;
	    public:
	        ProiettileDifensore();
	        ProiettileDifensore(Coordinate, Direzione, int, bool);
	        ProiettileDifensore(char, Coordinate, Direzione, int, bool);
	        ~ProiettileDifensore() override;
	
	        bool getSopraTerreno() const;
	        void setSopraTerreno(bool);
	    };
	}
#endif