#pragma once
#include "componente.hpp"

namespace skydda {
	class Terreno : public Componente {
    public:
        Terreno();
        Terreno(Coordinate);
        ~Terreno() override;
    };
}