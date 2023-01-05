#pragma once

#include <queue>
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
        void operator+(const Nemico&); // Gestire lo scontro con un nemico
        void operator+(const Nemico*);

        void stampa() override;
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
    private:
        bool sopraTerreno;
    public:
        ProiettileDifensore();
        ProiettileDifensore(Coordinate, Direzione, int);
        ProiettileDifensore(char, Coordinate, Direzione, int);
        ~ProiettileDifensore() override;

        bool getSopraTerreno() const;
        void setSopraTerreno(bool);
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

    class Mappa {
    private:
        Cursore cursore;
        std::vector<std::vector<Componente*>> mappa;
        std::queue<Effimera*> effimere; // Effimere presenti nella mappa, da rimuovere dopo un frame
        std::vector<Proiettile*> proiettili; // Proiettili presenti nella mappa (ridondante, ma necessario per individuarli velocemente)
        std::vector<Nemico*> nemici; // Nemici presenti nella mappa
        short int altezza;
        short int larghezza;

    public:
        Mappa();
        Mappa(short int, short int);
        ~Mappa();

        // Questi due metodi sono inutilissimi, ma li lascio per comodità
        short int getAltezza() const;
        short int getLarghezza() const;

        // Restituisce il puntatore al Componente in una posizione
        Componente* getComponente(Coordinate&) const;

        // Immissione bruta di un Componente in una posizione (senza controlli)
        void immettiComponente(Componente*, Coordinate&);
        void immettiComponente(Componente*);
        // Rimozione bruta di un Componente in una posizione
        void rimuoviComponente(Coordinate&);
        void rimuoviComponente(Componente*);

        // Immissione grafica di un Componente nel terminale (senza controlli, che si suppone vengano dall'alto)
        void stampaComponente(Coordinate&);
        void stampaComponente(Componente*);
        // Ripristino grafico di una cella nel terminale (senza controlli, che si suppone vengano dall'alto)
        void cancellaComponente(Coordinate&);
        void cancellaComponente(Componente*);

        void spostaComponente(Coordinate&, Coordinate&); // Questa è la funzione complessa: sposta un componente da una posizione ad un'altra, ma in questo deve anche saper gestire gli impatti con gli altri componenti
        void spostaComponente(Componente*, Coordinate&);

        void stampa() const;
    };
};