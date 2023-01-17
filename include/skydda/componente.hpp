#pragma once

#include "cursore.hpp"


namespace skydda {
    enum TipoComponente {
        __IGNOTO__,
        DIFENSORE,
        PROIETTILE_DIFENSORE,
        PROIETTILE_NEMICO,
        TERRENO
    };

    // https://www.ibm.com/docs/en/zos/2.4.0?topic=only-abstract-classes-c (Classi astratte pure)
    class Componente { // Classe astratta di base dalla quale ereditano tutti gli altri componenti
    protected:
        TipoComponente tipo; // Differenziare il tipo di componente
        char carattere;
        Coordinate coordinate;
        ANSI::Stile stile;
    
    public:
        Componente();
        Componente(char, Coordinate, ANSI::Stile, TipoComponente);
        virtual ~Componente() {} // Distruttore virtuale (https://github.com/FLAK-ZOSO/Sista/issues/2) (https://stackoverflow.com/questions/10338548/making-a-vector-of-instances-of-different-subclasses)

        TipoComponente getTipo() const;
        char getCarattere() const;
        void setCarattere(char);
        Coordinate getCoordinate() const;
        void setCoordinate(Coordinate);
        ANSI::Stile getStile() const;
        void setStile(ANSI::Stile);

        virtual void stampa();
    };
};