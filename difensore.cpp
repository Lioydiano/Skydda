#include "difensore.hpp"

namespace skydda {
    Difensore::Difensore(): Componente('1', Coordinate(0, 0), stileDifensore, TipoComponente::DIFENSORE) {} 
    Difensore::~Difensore() {}
    void Difensore::stampa() {
        stile.applica();
        std::cout << "$";
    }
}