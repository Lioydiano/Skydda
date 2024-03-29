#pragma once

#include <queue>
#include <vector>
#include <unordered_map>
#include "componente.hpp"


namespace skydda {
    enum Direzione { NORD, EST, SUD, OVEST };
    enum TipoProiettile { P_DIFENSORE, P_NEMICO };

    class Difensore;
    class Proiettile;
    class ProiettileDifensore;
    class ProiettileNemico;
    class Terreno;
    class Mappa;

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
        Proiettile(char, Coordinate, TipoProiettile, Direzione, int);
        ~Proiettile() override;

        TipoProiettile getOrigine() const;
        Direzione getDirezione() const;
        void setDirezione(Direzione);
        int getVelocita() const;

        Coordinate calcolaProssimaPosizione() const; // Calcola la prossima posizione del proiettile
    };

    class ProiettileDifensore : public Proiettile {
    private:
        bool sopraTerreno;
    public:
        ProiettileDifensore();
        ProiettileDifensore(Coordinate, Direzione, int, bool);
        ProiettileDifensore(char, Coordinate, Direzione, int, bool);
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
    };

    class Terreno : public Componente {
    public:
        Terreno();
        Terreno(Coordinate);
        ~Terreno() override;
    };

    class Mappa {
    private:
        Cursore cursore;
        std::vector<std::vector<Componente*>> mappa;
        std::vector<Proiettile*> proiettili; // Proiettili presenti nella mappa (ridondante, ma necessario per individuarli velocemente)
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

        // Immette un Componente nella mappa registrandolo in tutte le strutture dati necessarie
        void registraComponente(Proiettile*);

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

        void generaProiettile(Coordinate&, TipoProiettile, Direzione, int); // Genera un proiettile in una posizione (con controlli)

        void muoviProiettili(); // Muove tutti i proiettili nella mappa
        void rimuoviEffimere(); // Rimuove tutte le effimere nella mappa
        void azionaNemici(); // Fai compiere dei movimenti e sparare dei proiettili ai nemici

        void stampa() const;
    };
};