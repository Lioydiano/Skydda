#pragma once

#include <vector>
#include <unordered_map>
#include "componente.hpp"


namespace skydda {
    enum Direzione;
    enum TipoProiettile;
    std::unordered_map<Direzione, Coordinate> direzioni;
    std::unordered_map<Direzione, char> direzioneCarattere;

    class Difensore;
    class Nemico;
    class Proiettile;
    class ProiettileDifensore;
    class ProiettileNemico;
    class Terreno;
    class Effimera;
    class Mappa;

    class Nemico : public Componente {
    private:
        short int vita;
    
    public:
        Nemico();
        Nemico(char, Coordinate, short int);
        ~Nemico() override;

        short int getVita() const;
        void setVita(short int);

        void operator+(const ProiettileDifensore&); // Gestire lo scontro con un proiettile del difensore
        void operator+(const ProiettileDifensore*); // Gestire lo scontro con un proiettile del difensore
        void operator+(const ProiettileNemico&); // Gestire lo scontro con un proiettile nemico
        void operator+(const ProiettileNemico*); // Gestire lo scontro con un proiettile nemico
        void operator+=(const Nemico&); // Gestire lo scontro con un nemico
        void operator+=(const Nemico*);
    };

    class Difensore : public Componente {
    public:
        Difensore();
        ~Difensore() override;

        void stampa() override;
    };

    class Proiettile : public Componente {
    protected:
        TipoProiettile origine; // Differenziare l'origine
        Direzione direzione;
        int velocita;

    public:
        Proiettile();
        Proiettile(Coordinate, TipoProiettile, Direzione, int);
        Proiettile(char, Coordinate, TipoProiettile, Direzione);
        Proiettile(char, Coordinate, TipoProiettile, Direzione, int);
        ~Proiettile() override;

        TipoProiettile getOrigine() const;
        Direzione getDirezione() const;
        int getVelocita() const;

        Proiettile operator+(const Proiettile&); // Gestire lo scontro
        Proiettile operator+(const Proiettile*); // Gestire lo scontro
    };

    class ProiettileDifensore : public Proiettile {
    public:
        ProiettileDifensore();
        ProiettileDifensore(Coordinate, Direzione, int);
        ProiettileDifensore(char, Coordinate, Direzione, int);
        ~ProiettileDifensore() override;
    };

    class ProiettileNemico : public Proiettile {
    public:
        ProiettileNemico();
        ProiettileNemico(Coordinate, Direzione, int);
        ProiettileNemico(char, Coordinate, Direzione, int);
        ~ProiettileNemico() override;

        Effimera* operator+(ProiettileDifensore&); // Gestire lo scontro
        Effimera* operator+(ProiettileDifensore*); // Gestire lo scontro
    };

    class Terreno : public Componente {
    public:
        Terreno();
        Terreno(Coordinate);
        ~Terreno() override;
    };

    class Effimera : public Componente {
    public:
        Effimera();
        Effimera(Coordinate);
        ~Effimera() override;

        void stampa() override;
    };
};