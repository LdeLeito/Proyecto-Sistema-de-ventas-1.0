#ifndef VIAJES_H
#define VIAJES_H

#include "Pasajes.h"

struct Viaje
{
    int id_viaje;
    char destino[DESTINO_MAX];
    char fecha[FECHA_MAX];
    char horario[HORARIO_MAX];
    struct Pasaje pasajes[PASAJES_MAX];
    int asientos_ocupados[BUTACA_MAX + 1]; // 0 = libre, 1 = ocupado
    int cantidadPasajes;
};

int BuscarViajeCoincidente(struct Viaje *viajes, int cantidadViajes, const char *destino, const char *fecha, const char *horario);
int CrearViaje(struct Viaje *viajes, int *cantidadViajes, const char *destino, const char *fecha, const char *horario);
int BuscarButacaLibre(const struct Viaje *v);
int AsignarPasajeAViaje(struct Viaje *v, const struct Pasaje *p, int butacaDeseada);
void InicializarViaje(struct Viaje *v, int id_viaje, const char *destino, const char *fecha, const char *horario);

/* Orquestador */
void RegistrarPasajeEnViaje(struct Viaje *viajes, int *cantidadViajes, struct Pasajero *pasajeros, int cantidadPasajeros);

#endif // VIAJES_H