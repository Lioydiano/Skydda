#pragma once
#include "proiettile.hpp"

namespace skydda {
    class ProiettileNemico : public Proiettile {
    public:
        ProiettileNemico();
        ProiettileNemico(Coordinate, Direzione, int);
        ProiettileNemico(char, Coordinate, Direzione, int);
        ~ProiettileNemico() override;
    };
}