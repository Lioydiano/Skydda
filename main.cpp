#include <thread> // std::this_thread::sleep_for
#include <chrono> // std::chrono::milliseconds, std::chrono::seconds
#include <future> // std::async, std::Future
#include <random> // mt19937, bernoulli_distribution
#include <conio.h> // getch()

#include "ANSI.hpp"
#include "componente.hpp"
#include "coordinate.hpp"
#include "cursore.hpp"
#include "difensore.hpp"
#include "mappa.hpp"
#include "proiettile.hpp"
#include "proiettiledifensore.hpp"
#include "proiettilenemico.hpp"
#include "terreno.hpp"
// g++ main.cpp -o skydda -std=c++17 -Wall -O3


enum Mossa { // Associa una mossa ad un valore numerico per riconoscerla
    // Movimenti del difensore
    MossaSinistra,
    MossaDestra,
    MossaSu,
    MossaGiu,
    // Lancio di proiettili
    SparaSinistra,
    SparaDestra,
    SparaSu,
    SparaGiu,
    // Altre mosse
    NessunaMossa,
    MostraObiettivo, // Mostra l'obiettivo con una X
    Vinsten, // Tentativo di vittoria
    Abbandona, // Abbandona la partita (quando NON si è in pausa)
    Pausa, // Mette in pausa la partita
    Riprendi // Riprende la partita (quando si è in pausa)
};


void stampaIntro() {
    std::cout << "\x1b]2;Skydda\x07"; // Questo comando cambia il titolo della finestra
    std::cout << "\t\t\t\t      \033[035;1mSKYDDA\033[0m\n";
    std::cout << "\t\t\t\033[3mCapture the goal to become the goat\033[0m\n\n";

    std::cout << "\t\t\t  \x1b[31;1mElissx \t\tFLAK-ZOSO\x1b[0m\n\n";

    std::cout << "\t\t\t- \033[035m 'v'\033[0m to convalidate your path\n";
    std::cout << "\t\t\t- \033[035m 'q'\033[0m to quit\n";
    std::cout << "\t\t\t- \033[035m 'x'\033[0m show the goal with an \033[031mX\033[0m\n";
    std::cout << "\t\t\t- \033[035m 'p' 'r'\033[0m to pause/resume\n";
    std::cout << "\t\t\t- \033[035m 'w' 'a' 's' 'd'\033[0m to play\n";
    std::cout << "\t\t\t- \033[035m ^ > v <\033[0m (arrow keys) to shoot\n\n";

    std::cout << "\t\t\t\033[032m$\033[0m <---- this is you, the defender\n";
    std::cout << "\t\t\t\033[036m^\033[0m <---- this is an enemy bullet\n";
    std::cout << "\t\t\t\033[031mX\033[0m <---- this is the goal you need to reach\n\n";

    std::cout << "\t\t\tYou can hit your enemy with your bullets \033[035mv\033[0m\n";
    std::cout << "\t\tYou can make the bullets bounce, but we won't tell you how\n\n";

    std::cout << "     Remember: to win you must connect the goal to the origin {0, 0} with a complete road!\033[0m\n\n";
    std::cout << "\t\t\t\t\033[3;5mPress any key to start\033[0m\n";
    getch(); // Aspetta finché l'utente non preme un tasto (invia un carattere, char)
}


// Legge la mossa dell'utente, restituisce il valore numerico associato
Mossa leggiMossa() {
    char carattere = getch(); // Legge un carattere (invio di un tasto)
    if (carattere == -32) { // Se il carattere è -32, allora è stato premuto un tasto freccia (Eludi la [ che segue \033)
        // \033[ è il codice ASCII per il tasto freccia
        carattere = getch();
        switch (carattere) {
            case 72: // '\033[A' (ovvero '\03372' perché '['+'A'=72) è il codice ASCII per il tasto freccia su
                return SparaSu;
            case 80: // '\033[B' è il codice ASCII per il tasto freccia giù
                return SparaGiu;
            case 75: // '\033[D' è il codice ASCII per il tasto freccia sinistra
                return SparaSinistra;
            case 77: // '\033[C' è il codice ASCII per il tasto freccia destra
                return SparaDestra;
            default:
                break;
        }
    }
    switch (carattere) { // Per Muoversi
        case 'w': case 'W':
            return MossaSu;
        case 's': case 'S':
            return MossaGiu;
        case 'd': case 'D':
            return MossaDestra;
        case 'a': case 'A':
            return MossaSinistra;
        case 'x': case 'X':
            return MostraObiettivo;
        case 'v': case 'V':
            return Vinsten;
        case 'q': case 'Q':
            return Abbandona;
        case 'p': case 'P':
            return Pausa;
        case 'r': case 'R':
            return Riprendi;
        default:
            break;
    }
    return NessunaMossa;
}


int generaIsola(skydda::Mappa& mappa) {
    int larghezza = 15 + rand() % 5;
    skydda::Coordinate coordinate;
    for (int i = 0; i < larghezza; i++) {
        for (int j = 0; j < larghezza - i; j++) {
            coordinate.y = j;
            coordinate.x = i;
            mappa.immettiComponente(
                new skydda::Terreno(
                    coordinate
                ), coordinate
            );
        }
    }
    return larghezza;
}


void muoviDifensore(skydda::Mappa& mappa, skydda::Direzione direzione, skydda::Difensore& difensore) {
    skydda::Coordinate coordinate = difensore.getCoordinate() + skydda::direzioni[direzione]; // Calcola le coordinate di destinazione a seconda della direzione della mossa
    try {
        coordinate.valida(mappa.getAltezza(), mappa.getLarghezza());
    } catch (std::runtime_error& e) { // Il ramo di catch è eseguito se viene lanciata un'eccezione di tipo std::runtime_error
        return; // Se le coordinate non sono valide, non muovere il difensore, ma termina la funzione
    }
    skydda::Coordinate vecchie = difensore.getCoordinate(); // Memorizza le vecchie coordinate del difensore
    mappa.spostaComponente(vecchie, coordinate); // Sposta il difensore nella nuova posizione
}


skydda::Cursore cursore; // Cursore ausiliario per stampare le indicazioni
const skydda::Coordinate indicazioni_difensore(10, 70); // Coordinate del terminale dove stampare le indicazioni sul difensore
// Aggiorna le coordinate del difensore nella barra laterale di destra
void aggiornaCoordinateDifensore(skydda::Difensore& difensore) {
    cursore.posiziona(indicazioni_difensore);
    ANSI::reimposta();
    std::cout << "Difensore: (" << difensore.getCoordinate().y << ", " << difensore.getCoordinate().x << ")   ";
}

skydda::Coordinate generaCoordinate(skydda::Mappa& mappa) {
    skydda::Coordinate coordinate;
    while (true) {
        coordinate.x = rand() % mappa.getLarghezza();
        coordinate.y = rand() % mappa.getAltezza();
        if (mappa.getComponente(coordinate) == nullptr)
            break;
    }
    return coordinate;
}

// Stampa l'obiettivo nel terminale con una X rossa
void stampaObiettivo(skydda::Coordinate& obiettivo) {
    cursore.posiziona(obiettivo); // Posiziona il cursore alle coordinate dell'obiettivo
    skydda::stileDestinazione.applica(); // Applica lo stile della X rossa (skydda::stileDestinazione è un oggetto di tipo skydda::Stile)
    std::cout << "X"; // Stampa la X rossa
    ANSI::reimposta(); // Ripristina lo stile di default (per evitare che il terminale rimanga con lo stile della X rossa)
}

int main() {
    stampaIntro();
    srand(time(NULL)); // Inizializza il generatore di numeri casuali con il tempo attuale (perché se no le partite sono tutte uguali)
    std::chrono::milliseconds durata(100);

    skydda::Mappa mappa(50, 20);
	skydda::Difensore difensore;

    generaIsola(mappa);
    mappa.immettiComponente(&difensore);
    mappa.stampa();
    skydda::Coordinate obiettivo = generaCoordinate(mappa); // Coordinate obbiettivo
    stampaObiettivo(obiettivo);

    const skydda::Coordinate indicazioni_destinazione(8, 70); // Coordinate del terminale dove stampare le indicazioni sulla destinazione
    aggiornaCoordinateDifensore(difensore);
    cursore.posiziona(indicazioni_destinazione);
    ANSI::reimposta();
    std::cout << "Obiettivo: (" << obiettivo.y << ", " << obiettivo.x << ")";

    while (true) {
        // Lancia asincronamente la funzione leggiMossa, che attende un input da tastiera, e aspetta che sia pronta
        std::future<Mossa> mossa = std::async(std::launch::async, leggiMossa); // Il risultato della funzione leggiMossa viene custodito nel Future mossa
        // Nel frattempo va avanti, muove i proiettili e genera nuovi proiettili
        while (mossa.wait_for(durata) != std::future_status::ready) { // Se il Future mossa non è pronto, aspetta 100 millisecondi e riprova (muovendo i proiettili ecc. nel frattempo), altrimenti esce dal ciclo
            mappa.muoviProiettili();
            if (rand() % 5 == 0) { // Se il numero casuale è divisibile per cinque, quindi con probabilità 1/5, genera un proiettile nemico
                skydda::Coordinate coord(20, rand() % 50); // Genera una coordinata casuale sulla riga 20, quindi sul fondo della mappa
                mappa.generaProiettile(
                    coord, skydda::TipoProiettile::P_NEMICO,
                    skydda::Direzione::NORD, 1
                ); // Genera un proiettile nemico in quella coordinata, con direzione NORD (infatti tutti i proiettili vanno verso l'alto) e velocità 1
            }
        } // Quando il Future mossa è pronto, esce dal ciclo e continua
        Mossa m = mossa.get(); // Ottiene il risultato del Future mossa, che ora è pronto, tramite il metodo .get()
        switch (m) { // Switch sul tipo di mossa
            case Abbandona: {
                std::cout << "Hai abbandonato la partita" << std::endl;
                exit(0); // Termina il programma
            }
            case Pausa: {
                while (leggiMossa() != Riprendi); // Non fa nulla, aspetta che il gioco venga ripreso
                break;
            }
            case MostraObiettivo: {
                stampaObiettivo(obiettivo);
                break;
            }
            case MossaSinistra: {
                muoviDifensore(mappa, skydda::Direzione::OVEST, difensore);
                aggiornaCoordinateDifensore(difensore);
                break;
            }
            case MossaDestra: {
                muoviDifensore(mappa, skydda::Direzione::EST, difensore);
                aggiornaCoordinateDifensore(difensore);
                break;
            }
            case MossaSu: {
                muoviDifensore(mappa, skydda::Direzione::NORD, difensore);
                aggiornaCoordinateDifensore(difensore);
                break;
            }
            case MossaGiu: {
                muoviDifensore(mappa, skydda::Direzione::SUD, difensore);
                aggiornaCoordinateDifensore(difensore);
                break;
            }
            case SparaSinistra: case SparaDestra: case SparaSu: case SparaGiu: { // Se la mossa è uno dei quattro tipi di sparo
                skydda::Coordinate coordinate = difensore.getCoordinate(); // Ottiene le coordinate del difensore (che sono le coordinate dalle quali viene sparato il proiettile)
                switch (m) { // Switch sulla direzione dello sparo
                    case SparaSinistra:
                        mappa.generaProiettile(
                            coordinate, skydda::TipoProiettile::P_DIFENSORE, 
                            skydda::Direzione::OVEST, 1
                        ); // Genera un proiettile difensore in quelle coordinate, con direzione OVEST e velocità 1
                        break;
                    case SparaDestra:
                        mappa.generaProiettile(
                            coordinate, skydda::TipoProiettile::P_DIFENSORE, 
                            skydda::Direzione::EST, 1
                        ); // Genera un proiettile difensore in quelle coordinate, con direzione EST e velocità 1
                        break;
                    case SparaSu:
                        mappa.generaProiettile(
                            coordinate, skydda::TipoProiettile::P_DIFENSORE, 
                            skydda::Direzione::NORD, 1
                        ); // Genera un proiettile difensore in quelle coordinate, con direzione NORD e velocità 1
                        break;
                    case SparaGiu:
                        mappa.generaProiettile(
                            coordinate, skydda::TipoProiettile::P_DIFENSORE, 
                            skydda::Direzione::SUD, 1
                        ); // Genera un proiettile difensore in quelle coordinate, con direzione SUD e velocità 1
                        break;
                    default:
                        break;
                }
                break;
            }
            case NessunaMossa:
                break;
            case Vinsten: { // L'utente pensa di aver vinto
                skydda::Coordinate coordinate_difensore = difensore.getCoordinate();
                mappa.immettiComponente(new skydda::Terreno(coordinate_difensore), coordinate_difensore);
                skydda::Coordinate origine_(0, 0);
                skydda::Componente* origine = mappa.getComponente(origine_);
                skydda::Componente* componente = mappa.getComponente(obiettivo);
                if (componente != nullptr && origine != nullptr) { // Se l'obiettivo non è vuoto...
                    if (componente->getTipo() == skydda::TipoComponente::TERRENO && origine->getTipo() == skydda::TipoComponente::TERRENO) {
                        // BFS per trovare eventuali connessioni tra obiettivo e origine
                        std::queue<skydda::Coordinate> coda;
                        std::vector<std::vector<bool>> visitati(mappa.getAltezza());
                        for (int i=0; i<mappa.getAltezza(); i++) { // Per ogni riga
                            visitati[i].resize(mappa.getLarghezza(), false); // La allargo e inizializzo a false
                        }
                        coda.push(obiettivo); // Parto dall'obiettivo, e tento di raggiungere l'origine
                        skydda::Coordinate cima;
                        skydda::Coordinate coordinate_vicino;
                        while (!coda.empty()) {
                            cima = coda.front(); // Prendi l'ultimo della coda
                            coda.pop(); // Elimina l'ultimo della coda
                            visitati[cima.y][cima.x] = true; // Segno come visitato
                            if (cima.y == 0 && cima.x == 0)
                                break;

                            for (int i=0; i<4; i++) { // Itero sulle possibili direzioni
                                coordinate_vicino = cima + skydda::direzioni[(skydda::Direzione)i]; // Guardiamo il blocco in quella direzione
                                try {
                                    coordinate_vicino.valida(mappa.getAltezza(), mappa.getLarghezza());
                                    if (visitati[coordinate_vicino.y][coordinate_vicino.x]) // Se è già stato visitato, non lo considero
                                        continue;
                                    skydda::Componente* vicino = mappa.getComponente(coordinate_vicino);
                                    if (vicino != nullptr) {
                                        if (vicino->getTipo() == skydda::TipoComponente::TERRENO) {
                                            coda.push(coordinate_vicino); // Richiedo che venga esplorata la zona del vicino
                                        }
                                    }
                                } catch (std::runtime_error& e) {
                                    continue;
                                }
                            }
                        }
                        if (visitati[0][0]) { // Abbiamo visitato l'origine
                            skydda::Coordinate c_(22, 0);
                            cursore.posiziona(c_);
                            ANSI::reimposta();
                            std::cout << "Hai vinto!";
                            std::cin.get();
                            return 0;
                        } else {
                            return 0;
                        }
                    } else {
                        skydda::Coordinate c_(22, 0);
                        cursore.posiziona(c_);
                        ANSI::reimposta();
                        std::cout << "Hai perso!";
                        std::cin.get();
                        return 0;
                    }
                } else {
                    skydda::Coordinate c_(22, 0);
                    cursore.posiziona(c_);
                    ANSI::reimposta();
                    std::cout << "Hai perso!";
                    std::cin.get();
                    return 0;
                }
                return 0;
            }
            default:
                break;
        }
    }

    std::this_thread::sleep_for(durata);
    return 0;
}