/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 5/2/24.
** File description:
** scripting.c
*/

#include "../../include/mysh.h"

int get_nb_line(char *buff)
{
    int nb = 0;

    for (int i = 0; buff[i] != '\0'; i++) {
        if (buff[i] == '\n')
            nb++;
    }
    return nb;
}

char *get_path(char *str)
{
    char *new = malloc(sizeof(char) * strlen(str));
    int ind = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] == '.' || str[i] == '/') && i < 3)
            continue;
        new[ind] = str[i];
        ind++;
    }
    new[ind] = '\0';
    return new;
}

char *open_file(char *new)
{
    int fd = open(new, O_RDWR);
    struct stat st;
    char *buffer = NULL;

    if (stat(new, &st) < 0)
        return NULL;
    buffer = malloc(sizeof(char) * st.st_size + 1);
    if (read(fd, buffer, st.st_size) < 0)
        return NULL;
    buffer[st.st_size] = '\0';
    return buffer;
}

char **get_arg_script(char *str)
{
    char *new = get_path(str);
    int ind = 0;
    char *buffer = open_file(new);
    int nb_line = get_nb_line(buffer);
    char **new_arg = malloc(sizeof(char *) * nb_line + 1);
    char *token = strtok(buffer, "\n\0");

    while (token != NULL) {
        new_arg[ind] = strdup(token);
        ind++;
        token = strtok(NULL, "\n\0");
    }
    new_arg[ind] = NULL;
    return new_arg;
}
