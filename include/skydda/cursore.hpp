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
        Coordinate coordinate;

        Cursore() : coordinate() {
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
        void posiziona(unsigned short y_, unsigned short x_) {
            coordinate.y = y_;
            coordinate.x = x_;
            std::cout << CSI << y_ << ";" << x_ << "H"; // Se tu vuoi spostare il cursore in (5, 10), allora il codice ANSI sarà "\x1b5;100H"
        }
        void posiziona(Coordinate& coordinata) {
            coordinate = coordinata;
            std::cout << CSI << coordinata.y << ";" << coordinata.x << "H";
        }
    };
}