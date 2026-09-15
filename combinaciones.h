#ifndef COMBINACIONES_H
#define COMBINACIONES_H

int detectarHorizontales(const unsigned char* tablero, int filas, int columnas, unsigned char* marcador);
int detectarVerticales(const unsigned char* tablero, int filas, int columnas, unsigned char* marcador);
int eliminarMarcadas(unsigned char* tablero, int filas, int columnas, const unsigned char* marcador);

#endif // COMBINACIONES_H
