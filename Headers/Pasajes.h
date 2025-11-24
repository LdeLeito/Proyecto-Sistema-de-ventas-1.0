#ifndef PASAJES_H
#define PASAJES_H

#include "../Headers/Pasajeros.h"

#define PASAJES_MAX 40
#define DESTINO_MAX 50
#define FECHA_LEN 11
#define HORARIO_LEN 6
#define IDPASAJERO_LEN 6
#define VIAJES_MAX 100

struct Pasaje
{
    int id;
    int butaca;
    char destino[DESTINO_MAX];
    char fecha[FECHA_LEN];
    char horario[HORARIO_LEN];
    float costo;
    char id_pasajero[IDPASAJERO_LEN];
};

struct Viaje
{
    int id_viaje;
    char destino[DESTINO_MAX];
    char fecha[FECHA_LEN];
    char horario[HORARIO_LEN];
    struct Pasaje pasajes[PASAJES_MAX];
    int cantidadPasajes; // cuántos pasajes vendidos en este viaje
};

void RegistrarPasajeEnViaje(struct Viaje *viajes, int cantidadViajes, struct Pasajero *pasajeros, int cantidadPasajeros);
int BuscarViajeCoincidente(struct Viaje *viajes, int cantidadViajes, const char *destino, const char *fecha, const char *horario);
int CrearViaje(struct Viaje *viajes, int *cantidadViajes, const char *destino, const char *fecha, const char *horario);

#endif // PASAJES_H