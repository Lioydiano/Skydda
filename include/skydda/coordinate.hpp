#pragma once


namespace skydda {
    struct Coordinate { // Coordinate 2D [y, x] (y = riga, x = colonna) (0, 0) è in alto a sinistra
        unsigned short int y; // Non si accettano né i negativi né i numeri superiori a 65535
        unsigned short int x; // Non si accettano né i negativi né i numeri superiori a 65535

        Coordinate(): y(0), x(0) {}
        Coordinate(unsigned short int y_, unsigned short int x_): y(y_), x(x_) {}
        
        // "const Coordinate& coordinate" non fa modificare la variabile
        // "il 2°const" fa in modo che il metodo non possa modificare l'istanza corrente (this)
        // https://learn.microsoft.com/en-us/cpp/cpp/const-cpp?view=msvc-170
        Coordinate operator+(const Coordinate& coordinate) const { // Coordinate + coordinate
            return Coordinate(this->y + coordinate.y, this->x + coordinate.x);
        }
        bool operator==(const Coordinate& coordinate) const {
            return (this->y == coordinate.y && this->x == coordinate.x);
        }
    }; // matrice[y][x] - matrice[riga][colonna]
};