#ifndef TABLERO_H
#define TABLERO_H

void crearTablero(unsigned char** tablero, int filas, int columnas, int* bytesAsignados);
void liberarTablero(unsigned char** tablero);

unsigned char obtenerFicha(const unsigned char* tablero, int columnas, int fila, int columna);
void establecerFicha(unsigned char* tablero, int columnas, int fila, int columna, unsigned char valor);

void inicializarTableroAleatorio(unsigned char* tablero, int filas, int columnas);

#endif // TABLERO_H
