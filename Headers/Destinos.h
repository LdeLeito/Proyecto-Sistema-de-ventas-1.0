// headers/Destinos.h
#ifndef DESTINOS_H
#define DESTINOS_H

#define DESTINOS_MAX 50
#define DESTINO_NOMBRE_MAX 50

extern const char *destinosDisponibles[];
extern const int destinosCount;

void MostrarDestinosDisponibles(void);
int ValidarDestino(const char *destino);

#endif // DESTINOS_H