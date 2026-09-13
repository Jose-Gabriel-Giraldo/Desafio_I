#include "tablero.h"
#include "bits.h"
#include "fichas.h"

void crearTablero(unsigned char** tablero, int filas, int columnas, int* bytesAsignados)
{
    int bits = bitsNecesarios(filas, columnas);
    int bytes = bytesNecesarios(bits);

    *tablero = new unsigned char[bytes];
    for (int i = 0; i < bytes; i++)
    {
        (*tablero)[i] = 0;
    }

    *bytesAsignados = bytes;
}

void liberarTablero(unsigned char** tablero)
{
    delete[] *tablero;
    *tablero = nullptr;
}

unsigned char obtenerFicha(const unsigned char* tablero, int columnas, int fila, int columna)
{
    int pos = fila * columnas + columna;
    int bitInicial = pos * 3;
    return extraerBits3(tablero, bitInicial);
}

void establecerFicha(unsigned char* tablero, int columnas, int fila, int columna, unsigned char valor)
{
    int pos = fila * columnas + columna;
    int bitInicial = pos * 3;
    insertarBits3(tablero, bitInicial, valor);
}

void inicializarTableroAleatorio(unsigned char* tablero, int filas, int columnas)
{
    for (int f = 0; f < filas; f++)
    {
        for (int c = 0; c < columnas; c++)
        {
            establecerFicha(tablero, columnas, f, c, generarFichaAleatoria());
        }
    }
}
