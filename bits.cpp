#include "bits.h"

unsigned char extraerBits3(const unsigned char* buffer, int bitInicial)
{
    int byte = bitInicial / 8;
    int desfase = bitInicial % 8;
    bool cruzaByte = (desfase > 5);

    unsigned int ventana = buffer[byte];
    if (cruzaByte)
    {
        ventana = ventana | ((unsigned int)buffer[byte + 1] << 8);
    }

    return (unsigned char)((ventana >> desfase) & 0x07);
}

void insertarBits3(unsigned char* buffer, int bitInicial, unsigned char valor)
{
    int byte = bitInicial / 8;
    int desfase = bitInicial % 8;
    bool cruzaByte = (desfase > 5);

    unsigned int ventana = buffer[byte];
    if (cruzaByte)
    {
        ventana = ventana | ((unsigned int)buffer[byte + 1] << 8);
    }

    unsigned int mascara = (unsigned int)0x07 << desfase;
    unsigned int valorCorrido = ((unsigned int)(valor & 0x07)) << desfase;
    ventana = (ventana & ~mascara) ^ valorCorrido;

    buffer[byte] = (unsigned char)(ventana & 0xFF);
    if (cruzaByte)
    {
        buffer[byte + 1] = (unsigned char)((ventana >> 8) & 0xFF);
    }
}

int bitsNecesarios(int filas, int columnas)
{
    return 3 * filas * columnas;
}

int bytesNecesarios(int bits)
{
    return (bits + 7) / 8;
}
