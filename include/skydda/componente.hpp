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
        Componente();
        Componente(char, Coordinate, ANSI::Stile);
        virtual ~Componente() {} // Distruttore virtuale (https://github.com/FLAK-ZOSO/Sista/issues/2) (https://stackoverflow.com/questions/10338548/making-a-vector-of-instances-of-different-subclasses)

        char getCarattere() const;
        void setCarattere(char);
        Coordinate getCoordinate() const;
        void setCoordinate(Coordinate);
        ANSI::Stile getStile() const;
        void setStile(ANSI::Stile);
    };
};