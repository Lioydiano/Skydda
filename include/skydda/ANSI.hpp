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
    enum ColoreTesto;
    enum ColoreSfondo;
    enum Attributo;

    // https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
    void impostaColoreTesto(ColoreTesto);
    void impostaColoreSfondo(ColoreSfondo);
    void impostaAttributo(Attributo);
    void reimposta();

    struct Stile {
        ColoreTesto coloreTesto;
        ColoreSfondo coloreSfondo;
        Attributo attributo;

        Stile();
        Stile(ColoreTesto, ColoreSfondo, Attributo);

        void applica();
    };
};