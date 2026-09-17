#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H

void agregarFila(unsigned char** tablero, int* filas, int columnas, int* bytesAsignados, int posicion);
void eliminarFila(unsigned char** tablero, int* filas, int columnas, int* bytesAsignados, int posicion);
void agregarColumna(unsigned char** tablero, int filas, int* columnas, int* bytesAsignados, int posicion);
void eliminarColumna(unsigned char** tablero, int filas, int* columnas, int* bytesAsignados, int posicion);

int decidirRedimensionar(int bitsNecesariosNuevos, int bytesAsignadosActuales);

#endif // ESTRUCTURA_H
