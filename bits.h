#ifndef BITS_H
#define BITS_H

unsigned char extraerBits3(const unsigned char* buffer, int bitInicial);
void insertarBits3(unsigned char* buffer, int bitInicial, unsigned char valor);
int bitsNecesarios(int filas, int columnas);
int bytesNecesarios(int bits);

#endif // BITS_H
