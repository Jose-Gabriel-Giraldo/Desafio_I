#include "tablero.h"
#include "fichas.h"
#include "combinaciones.h"
#include "reorganizacion.h"
#include "estructura.h"
#include "estado.h"
#include "visualizacion.h"
#include <iostream>

using namespace std;

int main()
{
    inicializarGeneradorAleatorio();
    inicializarEstado();

    int filas, columnas;
    cout << "=== Sweet Crush ===" << endl;

    do
    {
        cout << "Numero de filas (minimo 3): ";
        cin >> filas;
    } while (filas < 3);

    do
    {
        cout << "Numero de columnas (minimo 3): ";
        cin >> columnas;
    } while (columnas < 3);

    unsigned char* tablero;
    int bytesAsignados;
    crearTablero(&tablero, filas, columnas, &bytesAsignados);
    inicializarTableroAleatorio(tablero, filas, columnas);

    // Resuelve combinaciones accidentales del llenado inicial antes de que
    // el jugador empiece, y reinicia el marcador para que no sumen puntos
    // que el jugador no gano con su propia jugada.
    int fichasIniciales = 0, combosIniciales = 0;
    procesarCascadas(tablero, filas, columnas, &fichasIniciales, &combosIniciales);
    inicializarEstado();

    int opcion = -1;
    while (opcion != 0)
    {
        cout << "\n--- Tablero actual (" << filas << "x" << columnas << ") ---" << endl;
        mostrarTableroFichas(tablero, filas, columnas);
        mostrarEstadisticas();

        cout << "\n1. Eliminar ficha" << endl;
        cout << "2. Agregar fila" << endl;
        cout << "3. Eliminar fila" << endl;
        cout << "4. Agregar columna" << endl;
        cout << "5. Eliminar columna" << endl;
        cout << "6. Ver tablero en binario" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1)
        {
            int f, c;
            cout << "Fila (0-" << (filas - 1) << "): ";
            cin >> f;
            cout << "Columna (0-" << (columnas - 1) << "): ";
            cin >> c;

            if (f < 0 || f >= filas || c < 0 || c >= columnas)
            {
                cout << "Posicion invalida." << endl;
            }
            else
            {
                establecerFicha(tablero, columnas, f, c, VACIO);
                registrarEliminacionManual();

                aplicarGravedad(tablero, filas, columnas);
                rellenarVacios(tablero, filas, columnas);

                int fe = 0, cd = 0;
                procesarCascadas(tablero, filas, columnas, &fe, &cd);
            }
        }
        else if (opcion == 2)
        {
            int pos;
            cout << "Posicion para la nueva fila (0-" << filas << "): ";
            cin >> pos;
            agregarFila(&tablero, &filas, columnas, &bytesAsignados, pos);
            int fe = 0, cd = 0;
            procesarCascadas(tablero, filas, columnas, &fe, &cd);
        }
        else if (opcion == 3)
        {
            int pos;
            cout << "Posicion de la fila a eliminar (0-" << (filas - 1) << "): ";
            cin >> pos;
            eliminarFila(&tablero, &filas, columnas, &bytesAsignados, pos);
            int fe = 0, cd = 0;
            procesarCascadas(tablero, filas, columnas, &fe, &cd);
        }
        else if (opcion == 4)
        {
            int pos;
            cout << "Posicion para la nueva columna (0-" << columnas << "): ";
            cin >> pos;
            agregarColumna(&tablero, filas, &columnas, &bytesAsignados, pos);
            int fe = 0, cd = 0;
            procesarCascadas(tablero, filas, columnas, &fe, &cd);
        }
        else if (opcion == 5)
        {
            int pos;
            cout << "Posicion de la columna a eliminar (0-" << (columnas - 1) << "): ";
            cin >> pos;
            eliminarColumna(&tablero, filas, &columnas, &bytesAsignados, pos);
            int fe = 0, cd = 0;
            procesarCascadas(tablero, filas, columnas, &fe, &cd);
        }
        else if (opcion == 6)
        {
            mostrarTableroBinario(tablero, filas, columnas, bytesAsignados);
        }
        else if (opcion != 0)
        {
            cout << "Opcion invalida." << endl;
        }
    }

    cout << "\nGracias por jugar. Puntuacion final: " << obtenerPuntuacion() << endl;

    liberarTablero(&tablero);
    return 0;
}
