#pragma once
#include "ANSI.hpp"

namespace ANSI {
    enum ColoreTesto {
        NERO = 30,
        ROSSO = 31,
        VERDE = 32,
        GIALLO = 33,
        BLU = 34,
        MAGENTA = 35,
        CIANO = 36,
        BIANCO = 37
    };
    enum ColoreSfondo {
        NERO = 40,
        ROSSO = 41,
        VERDE = 42,
        GIALLO = 43,
        BLU = 44,
        MAGENTA = 45,
        CIANO = 46,
        BIANCO = 47
    };
    enum Attributo {
        RIPRISTINO = 0,
        LUMINOSO = 1,
        FLEBILE = 2,
        CORSIVO = 3,
        SOTTOLINEATO = 4,
        LAMPEGGIA = 5,
        REVERSE = 6,
        NASCOSTO = 7
    };
    void impostaColoreTesto(ColoreTesto colore) {
        std::cout << CSI << colore << "m"; // Se il colore è 30 (ColoreTesto::NERO), allora il codice ANSI sarà "\x1b[30m"
    }
    void impostaColoreSfondo(ColoreSfondo colore) {
        std::cout << CSI << colore << "m"; // Se il colore è 40 (ColoreSfondo::NERO), allora il codice ANSI sarà "\x1b[40m"
    }
    void impostaAttributo(Attributo attributo) {
        std::cout << CSI << attributo << "m"; // Se l'attributo è 0 (Attributo::RIPRISTINO), allora il codice ANSI sarà "\x1b[0m"
    }
    void reimposta() {
        impostaColoreTesto(ColoreTesto::BIANCO);
        impostaColoreSfondo(ColoreSfondo::NERO);
        impostaAttributo(Attributo::RIPRISTINO);
    }

    Stile::Stile() {
        coloreTesto = ColoreTesto::BIANCO;
        coloreSfondo = ColoreSfondo::NERO;
        attributo = Attributo::RIPRISTINO;
    }
    Stile::Stile(ColoreTesto coloreTesto_, ColoreSfondo coloreSfondo_, Attributo attributo_) {
        this->coloreTesto = coloreTesto_;
        this->coloreSfondo = coloreSfondo_;
        this->attributo = attributo_;
    }
    void Stile::applica() {
        impostaColoreTesto(this->coloreTesto);
        impostaColoreSfondo(this->coloreSfondo);
        impostaAttributo(this->attributo);
    }
};