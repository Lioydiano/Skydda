#pragma once // Include guard (fa in modo che il file venga incluso una sola volta, anche se viene incluso più volte in un progetto)

#include <iostream> // std::cout

#define CSI "\x1b[" // Control Sequence Introducer
#define CLS "\x1b[2J" // Clear Screen
#define SSB "\x1b[3J" // Scroll Screen Buffer
#define NASCONDI_CURSORE "\x1b[?25l" // Hide cursor
#define MOSTRA_CURSORE "\x1b[?25h" // Show cursor
#define TL "\x1b[H" // Top Left (0,0)


// https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences
namespace ANSI { // Standard per gestire i colori e gli attributi del terminale
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

    // https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
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
        impostaColoreSfondo(ColoreSfondo::NERO);
        impostaColoreTesto(ColoreTesto::BIANCO);
        impostaAttributo(Attributo::RIPRISTINO);
    }

    struct Stile {
        ColoreTesto coloreTesto;
        ColoreSfondo coloreSfondo;
        Attributo attributo;

        Stile() { // default settings
            coloreTesto = ColoreTesto::BIANCO;
            coloreSfondo = ColoreSfondo::NERO;
            attributo = Attributo::RIPRISTINO;
        }
        Stile(ColoreTesto coloreTesto, ColoreSfondo coloreSfondo, Attributo attributo) {
            this->coloreTesto = coloreTesto;
            this->coloreSfondo = coloreSfondo;
            this->attributo = attributo;
        }
    
        void applica() {
            impostaColoreTesto(coloreTesto);
            impostaColoreSfondo(coloreSfondo);
            impostaAttributo(attributo);
        }
    };
};