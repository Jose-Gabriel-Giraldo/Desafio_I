#ifndef ESTADO_H
#define ESTADO_H

void inicializarEstado();

void registrarEliminacionManual();
void registrarFichasEliminadas(int cantidad);
void registrarCombinacion();
void registrarCascadas(int cantidad);
void registrarCascadasUltimaJugada(int cantidad);
void sumarPuntuacion(int puntos);

int obtenerEliminaciones();
int obtenerFichasEliminadas();
int obtenerCombinaciones();
int obtenerCascadas();
int obtenerCascadasUltimaJugada();
int obtenerPuntuacion();

#endif // ESTADO_H
