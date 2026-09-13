#include "fichas.h"
#include <cstdlib>
#include <ctime>

void inicializarGeneradorAleatorio()
{
    srand((unsigned int)time(nullptr));
}

unsigned char generarFichaAleatoria()
{
    unsigned char valor;
    do
    {
        valor = (unsigned char)(rand() & 0x07);
    } while (valor > 5);
    return valor;
}

char simboloFicha(unsigned char codigo)
{
    switch (codigo)
    {
    case FICHA_A: return 'A';
    case FICHA_B: return 'B';
    case FICHA_C: return 'C';
    case FICHA_D: return 'D';
    case FICHA_E: return 'E';
    case FICHA_F: return 'F';
    case VACIO:   return '.';
    default:      return '*';
    }
}
