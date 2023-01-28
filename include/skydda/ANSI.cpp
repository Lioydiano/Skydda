#pragma once
#include "ANSI.hpp"

namespace ANSI {
    void impostaColoreTesto(ColoreTesto colore) {
        std::cout << CSI << colore << "m"; // Se il colore è 30 (ColoreTesto::NERO), allora il codice ANSI sarà "\x1b[30m"
    }
    void impostaColoreSfondo(ColoreSfondo colore) {
        std::cout << CSI << colore << "m"; // Se il colore è 40 (ColoreSfondo::NERO), allora il codice ANSI sarà "\x1b[40m"
    }
    void impostaAttributo(Attributo attributo) {
        std::cout << CSI << attributo << "m"; // Se l'attributo è 0 (Attributo::RIPRISTINO), allora il codice ANSI sarà "\x1b[0m"
    }
    void reimposta() { // Ripristina lo stile di default (ColoreTesto::BIANCO, ColoreSfondo::NERO, Attributo::RIPRISTINO) nel terminale
        impostaColoreTesto(ColoreTesto::BIANCO);
        impostaColoreSfondo(ColoreSfondo::S_NERO);
        impostaAttributo(Attributo::RIPRISTINO);
    }

    Stile::Stile() {
        coloreTesto = ColoreTesto::BIANCO;
        coloreSfondo = ColoreSfondo::S_NERO;
        attributo = Attributo::RIPRISTINO;
    }
    Stile::Stile(ColoreTesto coloreTesto_, ColoreSfondo coloreSfondo_, Attributo attributo_) {
        coloreTesto = coloreTesto_;
        coloreSfondo = coloreSfondo_;
        attributo = attributo_;
    }
    void Stile::applica() {
        impostaColoreTesto(coloreTesto);
        impostaColoreSfondo(coloreSfondo);
        impostaAttributo(attributo);
    }
}