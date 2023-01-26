#ifndef TERRENO_hpp
	#define TERRENO_hpp
	#include "componente.hpp"
	
	namespace skydda {
		class Terreno : public Componente {
	    public:
	        Terreno();
	        Terreno(Coordinate);
	        ~Terreno() override;
	    };
	}
#endif