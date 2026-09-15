#ifndef REORGANIZACION_H
#define REORGANIZACION_H

void aplicarGravedad(unsigned char* tablero, int filas, int columnas);
void rellenarVacios(unsigned char* tablero, int filas, int columnas);
int procesarCascadas(unsigned char* tablero, int filas, int columnas, int* fichasEliminadas, int* combinacionesDetectadas);

#endif // REORGANIZACION_H
