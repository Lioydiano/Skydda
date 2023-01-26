#ifndef DIFENSORE_hpp
	#define DIFENSORE_hpp
	#include "componente.hpp"
	
	namespace skydda {
	    class Difensore : public Componente {
	    public:
	        Difensore();
	        ~Difensore() override;
	
	        void stampa() override;
	    };
	}
#endif