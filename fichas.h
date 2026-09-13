#ifndef FICHAS_H
#define FICHAS_H

const unsigned char FICHA_A = 0;
const unsigned char FICHA_B = 1;
const unsigned char FICHA_C = 2;
const unsigned char FICHA_D = 3;
const unsigned char FICHA_E = 4;
const unsigned char FICHA_F = 5;
const unsigned char VACIO = 6;
const unsigned char ESPECIAL = 7;

void inicializarGeneradorAleatorio();
unsigned char generarFichaAleatoria();
char simboloFicha(unsigned char codigo);

#endif // FICHAS_H
