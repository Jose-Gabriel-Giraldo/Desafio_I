#include "visualizacion.h"
#include "tablero.h"
#include "fichas.h"
#include "bits.h"
#include "estado.h"
#include <iostream>

using namespace std;

void mostrarTableroFichas(const unsigned char* tablero, int filas, int columnas)
{
    cout << "    ";
    for (int c = 0; c < columnas; c++)
    {
        cout << c << " ";
    }
    cout << endl;

    for (int f = 0; f < filas; f++)
    {
        cout << f << " | ";
        for (int c = 0; c < columnas; c++)
        {
            cout << simboloFicha(obtenerFicha(tablero, columnas, f, c)) << " ";
        }
        cout << endl;
    }
}

void mostrarTableroBinario(const unsigned char* tablero, int filas, int columnas, int bytesAsignados)
{
    int bits = bitsNecesarios(filas, columnas);
    cout << "Bits necesarios: " << bits << " | Bytes asignados: " << bytesAsignados << endl;

    for (int i = 0; i < bytesAsignados; i++)
    {
        cout << "Byte " << i << ": ";
        for (int b = 7; b >= 0; b--)
        {
            cout << ((tablero[i] >> b) & 1);
        }
        cout << endl;
    }
}

void mostrarEstadisticas()
{
    cout << "--- Estadisticas ---" << endl;
    cout << "Eliminaciones manuales     : " << obtenerEliminaciones() << endl;
    cout << "Fichas eliminadas total    : " << obtenerFichasEliminadas() << endl;
    cout << "Combinaciones detectadas   : " << obtenerCombinaciones() << endl;
    cout << "Cascadas (ultima jugada)   : " << obtenerCascadasUltimaJugada() << endl;
    cout << "Cascadas (total partida)   : " << obtenerCascadas() << endl;
    cout << "Puntuacion                 : " << obtenerPuntuacion() << endl;
}
