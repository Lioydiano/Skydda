#pragma once
#include "componente.hpp"

namespace skydda {
    class Difensore : public Componente {
    public:
        Difensore();
        ~Difensore() override;

        void stampa() override;
    };
}