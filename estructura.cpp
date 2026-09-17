#include "estructura.h"
#include "tablero.h"
#include "fichas.h"
#include "bits.h"

int decidirRedimensionar(int bitsNecesariosNuevos, int bytesAsignadosActuales)
{
    double uso = (double)bitsNecesariosNuevos / (bytesAsignadosActuales * 8.0);
    return uso < 0.65;
}

void agregarFila(unsigned char** tablero, int* filas, int columnas, int* bytesAsignados, int posicion)
{
    if (posicion < 0) posicion = 0;
    if (posicion > *filas) posicion = *filas;

    int filasNuevas = *filas + 1;
    int bytesNuevo = bytesNecesarios(bitsNecesarios(filasNuevas, columnas));

    unsigned char* destino = new unsigned char[bytesNuevo];
    for (int i = 0; i < bytesNuevo; i++)
    {
        destino[i] = 0;
    }

    for (int f = 0; f < filasNuevas; f++)
    {
        for (int c = 0; c < columnas; c++)
        {
            unsigned char valor;
            if (f == posicion)
            {
                valor = generarFichaAleatoria();
            }
            else
            {
                int fOrigen = (f < posicion) ? f : f - 1;
                valor = obtenerFicha(*tablero, columnas, fOrigen, c);
            }
            establecerFicha(destino, columnas, f, c, valor);
        }
    }

    delete[] *tablero;
    *tablero = destino;
    *filas = filasNuevas;
    *bytesAsignados = bytesNuevo;
}

void eliminarFila(unsigned char** tablero, int* filas, int columnas, int* bytesAsignados, int posicion)
{
    if (*filas <= 1) return;
    if (posicion < 0) posicion = 0;
    if (posicion >= *filas) posicion = *filas - 1;

    int filasNuevas = *filas - 1;
    int bitsNuevo = bitsNecesarios(filasNuevas, columnas);
    int bytesDestino = decidirRedimensionar(bitsNuevo, *bytesAsignados)
                           ? bytesNecesarios(bitsNuevo)
                           : *bytesAsignados;

    unsigned char* destino = new unsigned char[bytesDestino];
    for (int i = 0; i < bytesDestino; i++)
    {
        destino[i] = 0;
    }

    for (int f = 0; f < filasNuevas; f++)
    {
        int fOrigen = (f < posicion) ? f : f + 1;
        for (int c = 0; c < columnas; c++)
        {
            unsigned char valor = obtenerFicha(*tablero, columnas, fOrigen, c);
            establecerFicha(destino, columnas, f, c, valor);
        }
    }

    delete[] *tablero;
    *tablero = destino;
    *filas = filasNuevas;
    *bytesAsignados = bytesDestino;
}

void agregarColumna(unsigned char** tablero, int filas, int* columnas, int* bytesAsignados, int posicion)
{
    if (posicion < 0) posicion = 0;
    if (posicion > *columnas) posicion = *columnas;

    int columnasNuevas = *columnas + 1;
    int bytesNuevo = bytesNecesarios(bitsNecesarios(filas, columnasNuevas));

    unsigned char* destino = new unsigned char[bytesNuevo];
    for (int i = 0; i < bytesNuevo; i++)
    {
        destino[i] = 0;
    }

    for (int f = 0; f < filas; f++)
    {
        for (int c = 0; c < columnasNuevas; c++)
        {
            unsigned char valor;
            if (c == posicion)
            {
                valor = generarFichaAleatoria();
            }
            else
            {
                int cOrigen = (c < posicion) ? c : c - 1;
                valor = obtenerFicha(*tablero, *columnas, f, cOrigen);
            }
            establecerFicha(destino, columnasNuevas, f, c, valor);
        }
    }

    delete[] *tablero;
    *tablero = destino;
    *columnas = columnasNuevas;
    *bytesAsignados = bytesNuevo;
}

void eliminarColumna(unsigned char** tablero, int filas, int* columnas, int* bytesAsignados, int posicion)
{
    if (*columnas <= 1) return;
    if (posicion < 0) posicion = 0;
    if (posicion >= *columnas) posicion = *columnas - 1;

    int columnasNuevas = *columnas - 1;
    int bitsNuevo = bitsNecesarios(filas, columnasNuevas);
    int bytesDestino = decidirRedimensionar(bitsNuevo, *bytesAsignados)
                           ? bytesNecesarios(bitsNuevo)
                           : *bytesAsignados;

    unsigned char* destino = new unsigned char[bytesDestino];
    for (int i = 0; i < bytesDestino; i++)
    {
        destino[i] = 0;
    }

    for (int f = 0; f < filas; f++)
    {
        for (int c = 0; c < columnasNuevas; c++)
        {
            int cOrigen = (c < posicion) ? c : c + 1;
            unsigned char valor = obtenerFicha(*tablero, *columnas, f, cOrigen);
            establecerFicha(destino, columnasNuevas, f, c, valor);
        }
    }

    delete[] *tablero;
    *tablero = destino;
    *columnas = columnasNuevas;
    *bytesAsignados = bytesDestino;
}
