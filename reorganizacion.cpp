#include "reorganizacion.h"
#include "tablero.h"
#include "fichas.h"
#include "combinaciones.h"
#include "estado.h"

void aplicarGravedad(unsigned char* tablero, int filas, int columnas)
{
    for (int c = 0; c < columnas; c++)
    {
        int escritura = filas - 1;

        for (int lectura = filas - 1; lectura >= 0; lectura--)
        {
            unsigned char ficha = obtenerFicha(tablero, columnas, lectura, c);
            if (ficha != VACIO)
            {
                if (escritura != lectura)
                {
                    establecerFicha(tablero, columnas, escritura, c, ficha);
                }
                escritura--;
            }
        }

        for (int f = escritura; f >= 0; f--)
        {
            establecerFicha(tablero, columnas, f, c, VACIO);
        }
    }
}

void rellenarVacios(unsigned char* tablero, int filas, int columnas)
{
    for (int f = 0; f < filas; f++)
    {
        for (int c = 0; c < columnas; c++)
        {
            if (obtenerFicha(tablero, columnas, f, c) == VACIO)
            {
                establecerFicha(tablero, columnas, f, c, generarFichaAleatoria());
            }
        }
    }
}

int procesarCascadas(unsigned char* tablero, int filas, int columnas, int* fichasEliminadas, int* combinacionesDetectadas)
{
    int cascadas = 0;
    int total = filas * columnas;
    unsigned char* marcador = new unsigned char[total];

    while (true)
    {
        for (int i = 0; i < total; i++)
        {
            marcador[i] = 0;
        }

        int combosH = detectarHorizontales(tablero, filas, columnas, marcador);
        int combosV = detectarVerticales(tablero, filas, columnas, marcador);

        if (combosH == 0 && combosV == 0)
        {
            break;
        }

        int combosEstaVuelta = combosH + combosV;
        int eliminadasEstaVuelta = eliminarMarcadas(tablero, filas, columnas, marcador);

        *combinacionesDetectadas += combosEstaVuelta;
        *fichasEliminadas += eliminadasEstaVuelta;

        aplicarGravedad(tablero, filas, columnas);
        rellenarVacios(tablero, filas, columnas);

        cascadas++;

        // Puntuacion: 10 puntos por ficha eliminada, multiplicado por el nivel
        // de cascada (cascada 1 -> x1, cascada 2 -> x2, etc.), para premiar
        // las reacciones en cadena.
        for (int i = 0; i < combosEstaVuelta; i++)
        {
            registrarCombinacion();
        }
        registrarFichasEliminadas(eliminadasEstaVuelta);
        registrarCascadas(1);
        sumarPuntuacion(10 * eliminadasEstaVuelta * cascadas);
    }

    delete[] marcador;
    registrarCascadasUltimaJugada(cascadas);
    return cascadas;
}
