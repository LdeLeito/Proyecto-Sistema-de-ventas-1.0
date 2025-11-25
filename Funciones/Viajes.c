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
    // Evitar warnings
    (void)cantidadPasajeros;

    char destino[DESTINO_MAX];
    char fecha[FECHA_MAX];
    char horario[HORARIO_MAX];
    char idPasajero[IDPASAJERO_MAX];
    char costoStr[32];

    printf("----- Registro de Nuevo Pasaje -----\n");

    // Leer destino y validar
    printf("Ingrese destino: ");
    LeerCadenaSeguro(destino, DESTINO_MAX);
    if (!ValidarDestino(destino))
    {
        printf("Destino no disponible. Operación cancelada.\n");
        return;
    }

    // Leer fecha y horario (se puede mejorar validación de formato)
    printf("Ingrese fecha (dd/mm/yyyy): ");
    LeerCadenaSeguro(fecha, FECHA_MAX);
    printf("Ingrese horario (hh:mm): ");
    LeerCadenaSeguro(horario, HORARIO_MAX);

    // Buscar viaje existente
    int idxViaje = BuscarViajeCoincidente(viajes, *cantidadViajes, destino, fecha, horario);

    if (idxViaje >= 0 && viajes[idxViaje].cantidadPasajes >= PASAJES_MAX)
    {
        printf("El viaje encontrado (ID %d) está completo.\n", viajes[idxViaje].id_viaje);
        printf("Desea crear otro viaje con la misma ruta/fecha/horario? (s/n): ");
        char resp[4];
        LeerCadenaSeguro(resp, sizeof(resp));
        if (resp[0] == 's' || resp[0] == 'S')
        {
            int nuevoIdx = CrearViaje(viajes, cantidadViajes, destino, fecha, horario);
            if (nuevoIdx < 0)
            {
                printf("No se pudo crear nuevo viaje. Operación cancelada.\n");
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
            printf("No se pueden crear más viajes. Operación cancelada.\n");
            return;
        }
    }

    // Preparar pasaje
    struct Pasaje nuevo;
    InicializarPasaje(&nuevo);
    nuevo.id = viajes[idxViaje].cantidadPasajes + 1;
    strncpy(nuevo.destino, destino, DESTINO_MAX - 1);
    nuevo.destino[DESTINO_MAX - 1] = '\0';
    strncpy(nuevo.fecha, fecha, FECHA_MAX - 1);
    nuevo.fecha[FECHA_MAX - 1] = '\0';
    strncpy(nuevo.horario, horario, HORARIO_MAX - 1);
    nuevo.horario[HORARIO_MAX - 1] = '\0';

    // Costo con verificación
    printf("Ingrese costo: ");
    LeerCadenaSeguro(costoStr, sizeof(costoStr));
    char *endptr;
    nuevo.costo = strtof(costoStr, &endptr);
    if (endptr == costoStr || *endptr != '\0')
    {
        printf("Costo inválido. Operación cancelada.\n");
        return;
    }

    // Buscar butaca libre y permitir elección
    int butacaLibre = BuscarButacaLibre(&viajes[idxViaje]);
    if (butacaLibre == -1)
    {
        printf("Error: no hay butacas libres en este viaje.\n");
        return;
    }

    printf("Butaca sugerida: %d. Si desea otra, ingrese el número; ingrese 0 para aceptar la sugerida: ", butacaLibre);
    char butacaStr[8];
    LeerCadenaSeguro(butacaStr, sizeof(butacaStr));
    int butacaDeseada = atoi(butacaStr);
    if (butacaDeseada == 0)
        butacaDeseada = butacaLibre;

    if (!ValidarButaca(butacaDeseada))
    {
        printf("Butaca inválida. Operación cancelada.\n");
        return;
    }
    if (viajes[idxViaje].asientos_ocupados[butacaDeseada])
    {
        printf("Butaca %d ya está ocupada. Se asignará la primera libre.\n", butacaDeseada);
        butacaDeseada = BuscarButacaLibre(&viajes[idxViaje]);
        if (butacaDeseada == -1)
        {
            printf("No hay butacas libres. Operación cancelada.\n");
            return;
        }
    }

    // Leer y validar ID de pasajero: comprobar existencia en el arreglo
    printf("Ingrese ID del pasajero (ej: 00001): ");
    LeerCadenaSeguro(idPasajero, IDPASAJERO_MAX);
    idPasajero[IDPASAJERO_MAX - 1] = '\0';
    int pasajeroEncontrado = 0;
    for (int i = 0; i < cantidadPasajeros; ++i)
    {
        if (strcmp(pasajeros[i].idpasajero, idPasajero) == 0)
        {
            pasajeroEncontrado = 1;
            // opcional: mostrar nombre completo
            printf("Pasajero: %s %s\n", pasajeros[i].nombre, pasajeros[i].apellido);
            break;
        }
    }
    if (!pasajeroEncontrado)
    {
        printf("ID de pasajero no encontrado. Desea continuar y registrar el pasaje igual? (s/n): ");
        char resp2[4];
        LeerCadenaSeguro(resp2, sizeof(resp2));
        if (!(resp2[0] == 's' || resp2[0] == 'S'))
        {
            printf("Operación cancelada.\n");
            return;
        }
    }

    strncpy(nuevo.id_pasajero, idPasajero, IDPASAJERO_MAX - 1);
    nuevo.id_pasajero[IDPASAJERO_MAX - 1] = '\0';

    // Intentar asignar
    int asign = AsignarPasajeAViaje(&viajes[idxViaje], &nuevo, butacaDeseada);
    if (asign == 1)
    {
        printf("Pasaje registrado en viaje ID %d, butaca %d, pasaje ID %d\n",
               viajes[idxViaje].id_viaje, butacaDeseada, nuevo.id);

        // Persistencia: reescribir CSV completo (simple y consistente)
        if (!GuardarTodosLosViajesCSV(viajes, *cantidadViajes, "viajes_pasajes.csv"))
        {
            printf("Advertencia: no se pudo guardar en archivo.\n");
        }
    }
    else
    {
        // Mensajes claros según código de retorno
        if (asign == 0)
            printf("No se pudo asignar el pasaje: viaje lleno.\n");
        else if (asign == -1)
            printf("No se pudo asignar el pasaje: butaca inválida.\n");
        else if (asign == -2)
            printf("No se pudo asignar el pasaje: butaca ocupada.\n");
        else
            printf("No se pudo asignar el pasaje (código %d).\n", asign);
    }
}
