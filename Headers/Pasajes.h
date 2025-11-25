#ifndef PASAJES_H
#define PASAJES_H

#include "Pasajeros.h"

/* forward declaration para evitar dependencias circulares */
struct Viaje;

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

/* Prototipos: las firmas deben coincidir exactamente con las definiciones en .c */
void InicializarPasaje(struct Pasaje *p);
int ValidarButaca(int butaca);
void MostrarPasaje(const struct Pasaje *p);

/* Persistencia: usar struct Viaje por puntero (forward declaration permite esto) */
int GuardarPasajeEnArchivo(FILE *f, const struct Pasaje *p, int id_viaje);
int GuardarTodosLosViajesCSV(const struct Viaje *viajes, int cantidadViajes, const char *filename);
int CargarViajesDesdeCSV(struct Viaje *viajes, int *cantidadViajes, const char *filename);

#endif // PASAJES_H