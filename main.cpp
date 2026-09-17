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

    cout << "=== Sweet Crush ===" << endl;

    int filas;
    while (true)
    {
        cout << "Numero de filas (minimo 3, maximo 50): ";
        cin >> filas;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida: debe ser un numero entero." << endl;
            continue;
        }
        if (filas < 3 || filas > 50)
        {
            cout << "Fuera de rango: debe estar entre 3 y 50." << endl;
            continue;
        }
        break;
    }

    int columnas;
    while (true)
    {
        cout << "Numero de columnas (minimo 3, maximo 50): ";
        cin >> columnas;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida: debe ser un numero entero." << endl;
            continue;
        }
        if (columnas < 3 || columnas > 50)
        {
            cout << "Fuera de rango: debe estar entre 3 y 50." << endl;
            continue;
        }
        break;
    }

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

        while (true)
        {
            cout << "Opcion: ";
            cin >> opcion;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Entrada invalida: debe ser un numero entero." << endl;
                continue;
            }
            if (opcion < 0 || opcion > 6)
            {
                cout << "Fuera de rango: debe estar entre 0 y 6." << endl;
                continue;
            }
            break;
        }

        if (opcion == 1)
        {
            int f;
            while (true)
            {
                cout << "Fila a eliminar (0-" << (filas - 1) << "): ";
                cin >> f;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Entrada invalida: debe ser un numero entero." << endl;
                    continue;
                }
                if (f < 0 || f >= filas)
                {
                    cout << "Fuera de rango: debe estar entre 0 y " << (filas - 1) << "." << endl;
                    continue;
                }
                break;
            }

            int c;
            while (true)
            {
                cout << "Columna a eliminar (0-" << (columnas - 1) << "): ";
                cin >> c;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Entrada invalida: debe ser un numero entero." << endl;
                    continue;
                }
                if (c < 0 || c >= columnas)
                {
                    cout << "Fuera de rango: debe estar entre 0 y " << (columnas - 1) << "." << endl;
                    continue;
                }
                break;
            }

            establecerFicha(tablero, columnas, f, c, VACIO);
            registrarEliminacionManual();

            aplicarGravedad(tablero, filas, columnas);
            rellenarVacios(tablero, filas, columnas);

            int fe = 0, cd = 0;
            procesarCascadas(tablero, filas, columnas, &fe, &cd);
        }
        else if (opcion == 2)
        {
            int pos;
            while (true)
            {
                cout << "Posicion para la nueva fila (0-" << filas << "): ";
                cin >> pos;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Entrada invalida: debe ser un numero entero." << endl;
                    continue;
                }
                if (pos < 0 || pos > filas)
                {
                    cout << "Fuera de rango: debe estar entre 0 y " << filas << "." << endl;
                    continue;
                }
                break;
            }
            agregarFila(&tablero, &filas, columnas, &bytesAsignados, pos);
            int fe = 0, cd = 0;
            procesarCascadas(tablero, filas, columnas, &fe, &cd);
        }
        else if (opcion == 3)
        {
            int pos;
            while (true)
            {
                cout << "Posicion de la fila a eliminar (0-" << (filas - 1) << "): ";
                cin >> pos;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Entrada invalida: debe ser un numero entero." << endl;
                    continue;
                }
                if (pos < 0 || pos > filas - 1)
                {
                    cout << "Fuera de rango: debe estar entre 0 y " << (filas - 1) << "." << endl;
                    continue;
                }
                break;
            }
            eliminarFila(&tablero, &filas, columnas, &bytesAsignados, pos);
            int fe = 0, cd = 0;
            procesarCascadas(tablero, filas, columnas, &fe, &cd);
        }
        else if (opcion == 4)
        {
            int pos;
            while (true)
            {
                cout << "Posicion para la nueva columna (0-" << columnas << "): ";
                cin >> pos;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Entrada invalida: debe ser un numero entero." << endl;
                    continue;
                }
                if (pos < 0 || pos > columnas)
                {
                    cout << "Fuera de rango: debe estar entre 0 y " << columnas << "." << endl;
                    continue;
                }
                break;
            }
            agregarColumna(&tablero, filas, &columnas, &bytesAsignados, pos);
            int fe = 0, cd = 0;
            procesarCascadas(tablero, filas, columnas, &fe, &cd);
        }
        else if (opcion == 5)
        {
            int pos;
            while (true)
            {
                cout << "Posicion de la columna a eliminar (0-" << (columnas - 1) << "): ";
                cin >> pos;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Entrada invalida: debe ser un numero entero." << endl;
                    continue;
                }
                if (pos < 0 || pos > columnas - 1)
                {
                    cout << "Fuera de rango: debe estar entre 0 y " << (columnas - 1) << "." << endl;
                    continue;
                }
                break;
            }
            eliminarColumna(&tablero, filas, &columnas, &bytesAsignados, pos);
            int fe = 0, cd = 0;
            procesarCascadas(tablero, filas, columnas, &fe, &cd);
        }
        else if (opcion == 6)
        {
            mostrarTableroBinario(tablero, filas, columnas, bytesAsignados);
        }
    }

    cout << "\nGracias por jugar. Puntuacion final: " << obtenerPuntuacion() << endl;

    liberarTablero(&tablero);
    return 0;
}
