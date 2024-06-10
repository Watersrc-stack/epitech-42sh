/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 5/3/24.
** File description:
** initialize_next.c
*/

#include "../../../include/mysh.h"

char *verif_initilize(char *home, char *home_path)
{
    char *path = NULL;

    if (home_path != NULL) {
        home = my_strcat(home_path, "/");
        path = my_strcat(home, ".kehnsh_history");
        free(home);
        return path;
    } else {
        hist()->history = NULL;
        hist()->rev = NULL;
        return NULL;
    }
}

static void free_hist_link(void)
{
    history_t *tmp = hist()->rev;
    history_t *before = NULL;

    while (tmp != NULL) {
        free(tmp->cmd);
        before = tmp;
        tmp = tmp->next;
        free(before);
    }
}

void save_history_next(char *home_path)
{
    char *home = my_strcat(home_path, "/");
    char *path = my_strcat(home, ".kehnsh_history");
    int fd = open(path, O_RDWR | O_CREAT, 0666);

    if (hist()->history != NULL)
        write_struct_hist(hist()->history, fd);
    free_hist_link();
    free(home_path);
    free(home);
    free(path);
    close(fd);
}
