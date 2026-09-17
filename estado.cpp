#include "estado.h"

static int eliminacionesManual = 0;
static int fichasEliminadasTotal = 0;
static int combinacionesTotal = 0;
static int cascadasTotal = 0;
static int cascadasUltimaJugada = 0;
static int puntuacionTotal = 0;

void inicializarEstado()
{
    eliminacionesManual = 0;
    fichasEliminadasTotal = 0;
    combinacionesTotal = 0;
    cascadasTotal = 0;
    cascadasUltimaJugada = 0;
    puntuacionTotal = 0;
}

void registrarEliminacionManual()
{
    eliminacionesManual++;
}

void registrarFichasEliminadas(int cantidad)
{
    fichasEliminadasTotal += cantidad;
}

void registrarCombinacion()
{
    combinacionesTotal++;
}

void registrarCascadas(int cantidad)
{
    cascadasTotal += cantidad;
}

void registrarCascadasUltimaJugada(int cantidad)
{
    cascadasUltimaJugada = cantidad;
}

void sumarPuntuacion(int puntos)
{
    puntuacionTotal += puntos;
}

int obtenerEliminaciones()
{
    return eliminacionesManual;
}

int obtenerFichasEliminadas()
{
    return fichasEliminadasTotal;
}

int obtenerCombinaciones()
{
    return combinacionesTotal;
}

int obtenerCascadas()
{
    return cascadasTotal;
}

int obtenerCascadasUltimaJugada()
{
    return cascadasUltimaJugada;
}

int obtenerPuntuacion()
{
    return puntuacionTotal;
}
