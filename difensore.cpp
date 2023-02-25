#include "difensore.hpp"

namespace skydda {
    ANSI::Stile stileDifensore(ANSI::ColoreTesto::VERDE, ANSI::ColoreSfondo::S_ROSSO, ANSI::Attributo::LUMINOSO);
    Difensore::Difensore(): Componente('1', Coordinate(0, 0), stileDifensore, TipoComponente::DIFENSORE) {} 
    Difensore::~Difensore() {}
    void Difensore::stampa() {
        stile.applica();
        std::cout << "$";
    }
}