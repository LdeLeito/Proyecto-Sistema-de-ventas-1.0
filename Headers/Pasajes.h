#ifndef PASAJES.H
#define PASAJES.H

#define ID_MAX 2 
#define BUTACA_MAX 40
#define DESTINO_MAX 50
#define Fecha_MAX 11
#define HORARIO_MAX 5
#define COSTO_MAX 10
#define PASAJERO_MAX 40


struct Pasaje
{
    int id[BUTACA_MAX][ID_MAX];
    int butaca[BUTACA_MAX];
    char destino[DESTINO_MAX];
    char fecha[Fecha_MAX];
    char horario[HORARIO_MAX];
    char costo[COSTO_MAX];
    int cantpasajero[PASAJERO_MAX];
    int idpersona[PASAJERO_MAX];
    char id_pasajero[IDPASAJERO_MAX]; // Relación con pasajero
};
void RegistrarPasaje(struct Pasaje *pasajes, int *cantidadpasajes);
#endif // PASAJES_H