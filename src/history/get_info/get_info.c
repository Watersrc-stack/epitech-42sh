/*
** EPITECH PROJECT, 2024
** kehnsh
** File description:
** initialise_history.c
*/

#include "../../../include/mysh.h"

int get_ind_hist(char **tab)
{
    int nb = 0;

    for (int i = 0; tab[i] != NULL; i++) {
        if (tab[i][0] == '!') {
            nb = i;
            break;
        }
    }
    return nb;
}

char **caloc_array(int size)
{
    char **new = malloc(sizeof(char *) * size);

    for (int i = 0; i < size; i++)
        new[i] = NULL;
    return new;
}

int get_home_ind(char **env)
{
    int i = 0;

    for (; env[i] != NULL; i++) {
        if (strncmp(env[i], "HOME", 4) == 0)
            return (i);
    }
    return (-1);
}

int get_size_his(char *buff, int st)
{
    int nb = 0;

    for (int i = 0; buff[i] != '\0'; i++) {
        if (st > 0 && (buff[i] == ' ' || buff[i] == ':')) {
            st--;
            continue;
        }
        if (st > 0)
            continue;
        nb++;
    }
    return nb;
}
