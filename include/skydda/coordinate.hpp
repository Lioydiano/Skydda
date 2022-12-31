#pragma once


namespace skydda {
    struct Coordinate { // Coordinate 2D [y, x] (y = riga, x = colonna) (0, 0) è in alto a sinistra
        unsigned short int y; // Non si accettano né i negativi né i numeri superiori a 65535
        unsigned short int x;

        Coordinate();
        Coordinate(unsigned short int, unsigned short int);

        Coordinate operator+(const Coordinate& coordinate) const; // Coordinate + coordinate
        bool operator==(const Coordinate& coordinate) const;
    }; // matrice[y][x] - matrice[riga][colonna]
};