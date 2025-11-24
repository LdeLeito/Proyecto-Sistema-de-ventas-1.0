#ifndef PASAJES_H
#define PASAJES_H

#define ID_MAX 40
#define BUTACA_MAX 40
#define DESTINO_MAX 50
#define Fecha_MAX 11 // Formato "DD/MM/YYYY" + '\0'
#define HORARIO_MAX 6 // Formato "HH:MM" + '\0'
#define COSTO_MAX 10
#define PASAJES_MAX 40

struct Pasaje
{
    int id;
    int butaca;
    char destino[DESTINO_MAX];
    char fecha[Fecha_MAX];
    char horario[HORARIO_MAX];
    float costo;
    char pasajeros[ PASAJES_MAX]; // por cada viaje
    char id_pasajero[IDPASAJERO_MAX]; // Relación con pasajero
};
void RegistrarPasaje(struct Pasaje *pasajes, int *cantidadpasajes);
void GuardarPasajesEnArchivo(const struct Pasaje *pasajes, int cantidadPasajes);
#endif // PASAJES_H