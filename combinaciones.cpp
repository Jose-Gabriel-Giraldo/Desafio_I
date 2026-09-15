#include "combinaciones.h"
#include "tablero.h"
#include "fichas.h"

int detectarHorizontales(const unsigned char* tablero, int filas, int columnas, unsigned char* marcador)
{
    int combinaciones = 0;

    for (int f = 0; f < filas; f++)
    {
        int c = 0;
        while (c < columnas)
        {
            unsigned char ficha = obtenerFicha(tablero, columnas, f, c);
            int inicio = c;

            while (c < columnas && obtenerFicha(tablero, columnas, f, c) == ficha)
            {
                c++;
            }

            int longitud = c - inicio;
            if (ficha != VACIO && longitud >= 3)
            {
                combinaciones++;
                for (int k = inicio; k < c; k++)
                {
                    marcador[f * columnas + k] = 1;
                }
            }
        }
    }

    return combinaciones;
}

int detectarVerticales(const unsigned char* tablero, int filas, int columnas, unsigned char* marcador)
{
    int combinaciones = 0;

    for (int c = 0; c < columnas; c++)
    {
        int f = 0;
        while (f < filas)
        {
            unsigned char ficha = obtenerFicha(tablero, columnas, f, c);
            int inicio = f;

            while (f < filas && obtenerFicha(tablero, columnas, f, c) == ficha)
            {
                f++;
            }

            int longitud = f - inicio;
            if (ficha != VACIO && longitud >= 3)
            {
                combinaciones++;
                for (int k = inicio; k < f; k++)
                {
                    marcador[k * columnas + c] = 1;
                }
            }
        }
    }

    return combinaciones;
}

int eliminarMarcadas(unsigned char* tablero, int filas, int columnas, const unsigned char* marcador)
{
    int eliminadas = 0;

    for (int f = 0; f < filas; f++)
    {
        for (int c = 0; c < columnas; c++)
        {
            if (marcador[f * columnas + c])
            {
                establecerFicha(tablero, columnas, f, c, VACIO);
                eliminadas++;
            }
        }
    }

    return eliminadas;
}
