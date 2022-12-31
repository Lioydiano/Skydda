#pragma once

#include "cursore.hpp"


namespace skydda {
    // https://www.ibm.com/docs/en/zos/2.4.0?topic=only-abstract-classes-c (Classi astratte pure)
    class Componente { // Classe astratta di base dalla quale ereditano tutti gli altri componenti
    protected:
        char carattere;
        Coordinate coordinata;
        ANSI::Stile stile;
    
    public:
        Componente() : coordinata(), stile(), carattere() {}
        Componente(char carattere_, Coordinate coordinata_, ANSI::Stile stile_) : carattere(carattere_), coordinata(coordinata_), stile(stile_) {}
        virtual ~Componente() {} // Distruttore virtuale (https://github.com/FLAK-ZOSO/Sista/issues/2) (https://stackoverflow.com/questions/10338548/making-a-vector-of-instances-of-different-subclasses)
    };
};