#pragma once

#include "ANSI.hpp"
#include "coordinate.hpp"


namespace skydda {
    void pulisciSchermo() {
        std::cout << CLS; // Pulisci lo schermo
        std::cout << SSB; // Pulisci la memoria dello schermo
        std::cout << TL; // Posiziona il cursore in alto a sinistra
    }

    struct Cursore {
        int y;
        int x;

        Cursore() : y(0), x(0) {
            pulisciSchermo();
            nascondi(); // Nascondi il cursore
        }
        ~Cursore() { // Distruttore che viene chiamato quando finisce il programma
            ANSI::reimposta(); // Ripristina i colori e gli attributi del terminale
            pulisciSchermo();
            mostra(); // Mostra il cursore (perché lo nascondiamo nel costruttore 
        }

        void nascondi() {
            std::cout << NASCONDI_CURSORE;
        }
        void mostra() {
            std::cout << MOSTRA_CURSORE;
        }
    
        // https://stackoverflow.com/questions/69597466/move-cursor-escape-sequence
        // https://tldp.org/HOWTO/Bash-Prompt-HOWTO/x361.html
        void posiziona(int y_, int x_) {
            this->y = y_;
            this->x = x_;
            std::cout << CSI << y << ";" << x << "H"; // Se tu vuoi spostare il cursore in (5, 10), allora il codice ANSI sarà "\x1b5;100H"
        }
        void posiziona(Coordinate& coordinata) {
            posiziona(coordinata.y, coordinata.x); // Chiamiamo la funzione sopra
        }
    };
}