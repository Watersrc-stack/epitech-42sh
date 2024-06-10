/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** my_getenv
*/

#include "../../include/mysh.h"
#include <stddef.h>

char *my_getenv(char *name, char **env)
{
    int len = strlen(name);

    for (int i = 0; env[i] != NULL; i++) {
        if (strncmp(env[i], name, len) == 0 && env[i][len] == '=') {
            return &env[i][len + 1];
        }
    }
    return NULL;
}
