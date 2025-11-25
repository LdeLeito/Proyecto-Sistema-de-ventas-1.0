#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/Viajes.h"
#include "../headers/Pasajeros.h"
#include "../headers/Destinos.h"
#include "../headers/Utiles.h"
#include "../headers/Pasajes.h"
#include "../headers/Fecha.h"

int BuscarViajeCoincidente(struct Viaje *viajes, int cantidadViajes, const char *destino, const char *fecha, const char *horario)
{
    for (int i = 0; i < cantidadViajes; ++i)
    {
        if (strcmp(viajes[i].destino, destino) == 0 &&
            strcmp(viajes[i].fecha, fecha) == 0 &&
            strcmp(viajes[i].horario, horario) == 0)
        {
            return i;
        }
    }
    return -1;
}

void InicializarViaje(struct Viaje *v, int id_viaje, const char *destino, const char *fecha, const char *horario)
{
    v->id_viaje = id_viaje;
    strncpy(v->destino, destino, DESTINO_MAX - 1);
    v->destino[DESTINO_MAX - 1] = '\0';
    strncpy(v->fecha, fecha, FECHA_MAX - 1);
    v->fecha[FECHA_MAX - 1] = '\0';
    strncpy(v->horario, horario, HORARIO_MAX - 1);
    v->horario[HORARIO_MAX - 1] = '\0';
    v->cantidadPasajes = 0;
    for (int i = 0; i <= BUTACA_MAX; ++i)
        v->asientos_ocupados[i] = 0;
}

int CrearViaje(struct Viaje *viajes, int *cantidadViajes, const char *destino, const char *fecha, const char *horario)
{
    if (*cantidadViajes >= VIAJES_MAX)
        return -1;
    int idx = *cantidadViajes;
    InicializarViaje(&viajes[idx], idx + 1, destino, fecha, horario);
    (*cantidadViajes)++;
    return idx;
}

int BuscarButacaLibre(const struct Viaje *v)
{
    for (int i = 1; i <= BUTACA_MAX; ++i)
    {
        if (!v->asientos_ocupados[i])
            return i;
    }
    return -1;
}

/* Asigna un pasaje a un viaje. Retorna:
   1 = éxito, 0 = viaje lleno, -1 = butaca inválida, -2 = butaca ocupada */
int AsignarPasajeAViaje(struct Viaje *v, const struct Pasaje *p, int butacaDeseada)
{
    if (v->cantidadPasajes >= PASAJES_MAX)
        return 0;
    if (!ValidarButaca(butacaDeseada))
        return -1;
    if (v->asientos_ocupados[butacaDeseada])
        return -2;

    /* copiar pasaje en la siguiente posición */
    v->pasajes[v->cantidadPasajes] = *p;
    v->pasajes[v->cantidadPasajes].butaca = butacaDeseada;
    v->asientos_ocupados[butacaDeseada] = 1;
    v->cantidadPasajes++;
    return 1;
}

/* Orquestador: pide datos, busca/crea viaje, asigna pasaje y guarda en CSV */
void RegistrarPasajeEnViaje(struct Viaje *viajes, int *cantidadViajes, struct Pasajero *pasajeros, int cantidadPasajeros)
{
    char destino[DESTINO_MAX];
    char fecha[FECHA_MAX];
    char horario[HORARIO_MAX];
    char idPasajero[IDPASAJERO_MAX];
    char costoStr[32];

    printf("Ingrese destino: ");
    LeerCadenaSeguro(destino, DESTINO_MAX);
    if (!ValidarDestino(destino))
    {
        printf("Destino no disponible.\n");
        return;
    }

    printf("Ingrese fecha (dd/mm/yyyy): ");
    LeerCadenaSeguro(fecha, FECHA_MAX);
    printf("Ingrese horario (hh:mm): ");
    LeerCadenaSeguro(horario, HORARIO_MAX);

    int idxViaje = BuscarViajeCoincidente(viajes, *cantidadViajes, destino, fecha, horario);
    if (idxViaje >= 0 && viajes[idxViaje].cantidadPasajes >= PASAJES_MAX)
    {
        printf("El viaje está completo. Desea crear otro viaje con la misma ruta? (s/n): ");
        char resp[4];
        LeerCadenaSeguro(resp, sizeof(resp));
        if (resp[0] == 's' || resp[0] == 'S')
        {
            int nuevoIdx = CrearViaje(viajes, cantidadViajes, destino, fecha, horario);
            if (nuevoIdx < 0)
            {
                printf("No se pudo crear nuevo viaje.\n");
                return;
            }
            idxViaje = nuevoIdx;
        }
        else
        {
            printf("Operación cancelada.\n");
            return;
        }
    }
    else if (idxViaje < 0)
    {
        idxViaje = CrearViaje(viajes, cantidadViajes, destino, fecha, horario);
        if (idxViaje < 0)
        {
            printf("No se pueden crear más viajes.\n");
            return;
        }
    }

    /* preparar pasaje */
    struct Pasaje nuevo;
    InicializarPasaje(&nuevo);
    nuevo.id = viajes[idxViaje].cantidadPasajes + 1;
    strncpy(nuevo.destino, destino, DESTINO_MAX - 1);
    strncpy(nuevo.fecha, fecha, FECHA_MAX - 1);
    strncpy(nuevo.horario, horario, HORARIO_MAX - 1);

    printf("Ingrese costo: ");
    LeerCadenaSeguro(costoStr, sizeof(costoStr));
    nuevo.costo = strtof(costoStr, NULL);

    /* elegir butaca: preguntar al usuario o asignar la primera libre */
    int butacaLibre = BuscarButacaLibre(&viajes[idxViaje]);
    if (butacaLibre == -1)
    {
        printf("Error: no hay butacas libres (esto no debería ocurrir aquí).\n");
        return;
    }
    printf("Butaca sugerida: %d. Desea otra butaca? (ingrese número o 0 para aceptar sugerida): ", butacaLibre);
    char butacaStr[8];
    LeerCadenaSeguro(butacaStr, sizeof(butacaStr));
    int butacaDeseada = atoi(butacaStr);
    if (butacaDeseada == 0)
        butacaDeseada = butacaLibre;

    if (!ValidarButaca(butacaDeseada))
    {
        printf("Butaca inválida.\n");
        return;
    }
    if (viajes[idxViaje].asientos_ocupados[butacaDeseada])
    {
        printf("Butaca ocupada. Asignando primera libre.\n");
        butacaDeseada = BuscarButacaLibre(&viajes[idxViaje]);
        if (butacaDeseada == -1)
        {
            printf("No hay butacas libres.\n");
            return;
        }
    }

    printf("Ingrese ID del pasajero: ");
    LeerCadenaSeguro(idPasajero, IDPASAJERO_MAX);
    strncpy(nuevo.id_pasajero, idPasajero, IDPASAJERO_MAX - 1);

    int asign = AsignarPasajeAViaje(&viajes[idxViaje], &nuevo, butacaDeseada);
    if (asign == 1)
    {
        printf("Pasaje registrado en viaje ID %d, butaca %d\n", viajes[idxViaje].id_viaje, butacaDeseada);
        /* persistir todos los viajes (opción simple) */
        if (!GuardarTodosLosViajesCSV(viajes, *cantidadViajes, "viajes_pasajes.csv"))
        {
            printf("Advertencia: no se pudo guardar en archivo.\n");
        }
    }
    else
    {
        printf("No se pudo asignar el pasaje (código %d).\n", asign);
    }
}