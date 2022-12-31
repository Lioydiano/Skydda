#pragma once

#include "cursore.hpp"


namespace skydda {
    // https://www.ibm.com/docs/en/zos/2.4.0?topic=only-abstract-classes-c (Classi astratte pure)
    class Componente { // Classe astratta di base dalla quale ereditano tutti gli altri componenti
    protected:
        char carattere;
        Coordinate coordinate;
        ANSI::Stile stile;
    
    public:
        Componente() : coordinate(), stile(), carattere() {}
        Componente(char, Coordinate, ANSI::Stile);
        virtual ~Componente() {} // Distruttore virtuale (https://github.com/FLAK-ZOSO/Sista/issues/2) (https://stackoverflow.com/questions/10338548/making-a-vector-of-instances-of-different-subclasses)
    };
};