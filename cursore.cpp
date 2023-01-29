#include "cursore.hpp"


namespace skydda {
    void pulisciSchermo() {
        std::cout << CLS; // Pulisci lo schermo
        std::cout << SSB; // Pulisci la memoria dello schermo
        std::cout << TL; // Posiziona il cursore in alto a sinistra
    }

    Cursore::Cursore() {
        pulisciSchermo();
        nascondi();
    }
    Cursore::~Cursore() { // Distruttore che viene chiamato quando finisce il programma
        ANSI::reimposta(); // Ripristina i colori e gli attributi del terminale
        pulisciSchermo();
        mostra(); // Mostra il cursore (perché lo nascondiamo nel costruttore 
    }
    void Cursore::nascondi() {
        std::cout << NASCONDI_CURSORE;
    }
    void Cursore::mostra() {
        std::cout << MOSTRA_CURSORE;
    }
    void Cursore::posiziona(unsigned short y_, unsigned short x_) {
        coordinate.y = y_ + 2;
        coordinate.x = x_ + 2;
        // https://stackoverflow.com/questions/69597466/move-cursor-escape-sequence
        // https://tldp.org/HOWTO/Bash-Prompt-HOWTO/x361.html
        std::cout << CSI << coordinate.y << ";" << coordinate.x << "H"; // Se tu vuoi spostare il cursore in (5, 10), allora il codice ANSI sarà "\x1b5;10H"
    }
    void Cursore::posiziona(const Coordinate& coordinate_) {
        coordinate = coordinate_;
        coordinate.y += 2;
        coordinate.x += 2;
        std::cout << CSI << coordinate.y << ";" << coordinate.x << "H"; // Se tu vuoi spostare il cursore in (5, 10), allora il codice ANSI sarà "\x1b5;10H"
    }
};