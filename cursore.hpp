#pragma once
#include "ANSI.hpp"
#include "coordinate.hpp"


namespace skydda {
    void pulisciSchermo();

    struct Cursore {
        Coordinate coordinate;

        Cursore();
        ~Cursore();

        void nascondi();
        void mostra();
        void posiziona(unsigned short, unsigned short);
        void posiziona(const Coordinate&);
    };
}