#include <string.h>
#include <stdio.h>
#include "../headers/Utiles.h"
void LeerCadenaSeguro(char *buffer, int len)
{
    if (fgets(buffer, len, stdin) == NULL)
    {
        buffer[0] = '\0';
        return;
    }
    size_t l = strlen(buffer);
    if (l > 0 && buffer[l - 1] == '\n')
        buffer[l - 1] = '\0';
}