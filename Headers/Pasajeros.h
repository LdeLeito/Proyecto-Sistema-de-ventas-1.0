#ifndef PASAJEROS_H
#define PASAJEROS_H

// Definiciones de constantes para las variables de los pasajeros
#define NOMBRE_MAX 30
#define APELLIDO_MAX 30
#define DNI_MAX 15
#define EMAIL_MAX 30
#define TELEFONO_MAX 15
#define DIR_MAX 100
// Esto definirá la cantidad de pasajeros, usamos 5 digitos del 0 al 9.
// Es decir podemos registrar hasta 99999 pasajeros
#define IDPASAJERO_MAX 5

struct Pasajero
{
    char idpasajero[IDPASAJERO_MAX];
    char nombre[NOMBRE_MAX];
    char apellido[APELLIDO_MAX];
    char dni[DNI_MAX];
    char email[EMAIL_MAX];
    char telefono[TELEFONO_MAX];
    char direccion[DIR_MAX];
};

void RegistrarPasajero(struct Pasajero *pasajeros, int *cantidadPasajeros);
void ListarPasajeros(const struct Pasajero *pasajeros, int cantidadPasajeros);
#endif // PASAJEROS_H
