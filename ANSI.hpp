// #pragma once // Include guard (fa in modo che il file venga incluso una sola volta, anche se viene incluso più volte in un progetto)
#ifndef ANSI_hpp
	#define ANSI_hpp
	#include <iostream> // std::cout
	
	#define CSI "\x1b[" // Control Sequence Introducer
	#define CLS "\x1b[2J" // Clear Screen
	#define SSB "\x1b[3J" // Scroll Screen Buffer
	#define NASCONDI_CURSORE "\x1b[?25l" // Hide cursor
	#define MOSTRA_CURSORE "\x1b[?25h" // Show cursor
	#define TL "\x1b[H" // Top Left (0,0)
	
	
	// https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences
	namespace ANSI { // Standard per gestire i colori e gli attributi del terminale
	    enum ColoreTesto {
	        NERO = 30,
	        ROSSO = 31,
	        VERDE = 32,
	        GIALLO = 33,
	        BLU = 34,
	        MAGENTA = 35,
	        CIANO = 36,
	        BIANCO = 37
	    };
	    enum ColoreSfondo {
	        S_NERO = 40,
	        S_ROSSO = 41,
	        S_VERDE = 42,
	        S_GIALLO = 43,
	        S_BLU = 44,
	        S_MAGENTA = 45,
	        S_CIANO = 46,
	        S_BIANCO = 47
	    };
	    enum Attributo {
	        RIPRISTINO = 0,
	        LUMINOSO = 1,
	        FLEBILE = 2,
	        CORSIVO = 3,
	        SOTTOLINEATO = 4,
	        LAMPEGGIA = 5,
	        REVERSE = 6,
	        NASCOSTO = 7
	    };
	
	    // https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
	    void impostaColoreTesto(ColoreTesto);
	    void impostaColoreSfondo(ColoreSfondo);
	    void impostaAttributo(Attributo);
	    void reimposta();
	
	    struct Stile {
	        ColoreTesto coloreTesto;
	        ColoreSfondo coloreSfondo;
	        Attributo attributo;
	
	        Stile();
	        Stile(ColoreTesto, ColoreSfondo, Attributo);
	
	        void applica();
	    };
	};
#endif