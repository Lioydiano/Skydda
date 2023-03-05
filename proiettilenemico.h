#ifndef PROIETTILENEMICO_hpp
	#define PROIETTILENEMICO_hpp
	#include "proiettiledifensore.h"
	
	namespace skydda {
	    class ProiettileNemico : public Proiettile {
	    public:
	        ProiettileNemico();
	        ProiettileNemico(Coordinate, Direzione, int);
	        ProiettileNemico(char, Coordinate, Direzione, int);
	        ~ProiettileNemico() override;
	    };
	}
#endif