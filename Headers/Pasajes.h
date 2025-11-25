#ifndef PASAJES_H
#define PASAJES_H

#include "../Headers/Pasajeros.h"

#define PASAJES_MAX 40
#define BUTACA_MAX 40
#define DESTINO_MAX 50
#define FECHA_MAX 11
#define HORARIO_MAX 6
#define IDPASAJERO_MAX 6
#define VIAJES_MAX 100

struct Pasaje
{
    int id;
    int butaca;
    char destino[DESTINO_MAX];
    char fecha[FECHA_MAX];
    char horario[HORARIO_MAX];
    float costo;
    char id_pasajero[IDPASAJERO_MAX];
};

struct Viaje
{
    int id_viaje;
    char destino[DESTINO_MAX];
    char fecha[FECHA_MAX];
    char horario[HORARIO_MAX];
    struct Pasaje pasajes[PASAJES_MAX];
    int asientos_ocupados[BUTACA_MAX + 1]; // 0 = libre, 1 = ocupado
    int cantidadPasajes;                   // cuántos pasajes vendidos en este viaje
};

void RegistrarPasajeEnViaje(struct Viaje *viajes, int cantidadViajes, struct Pasajero *pasajeros, int cantidadPasajeros);
int BuscarViajeCoincidente(struct Viaje *viajes, int cantidadViajes, const char *destino, const char *fecha, const char *horario);
int CrearViaje(struct Viaje *viajes, int *cantidadViajes, const char *destino, const char *fecha, const char *horario);

#endif // PASAJES_H