/*
** EPITECH PROJECT, 2024
** kehnsh
** File description:
** initialise_history.c
*/

#include "../../include/mysh.h"

static char operators[] = {'|', '>', '<', '&', ';', ' ', '\0'};

struct passer {
    int index;
    int ind;
    int sep;
    int i;
};

static void assign_tab(char *buff, char **tab, int *index, int *ind)
{
    buff[*ind] = '\0';
    tab[*index] = strdup(buff);
    *ind = 0;
    *index += 1;
    free(buff);
}

static int verif_sep(char c)
{
    for (int i = 0; operators[i] != '\0'; i++)
        if (operators[i] == c)
            return 1;
    return 0;
}

int gen_tab_line_cond(char *line, struct passer *pas, char *buff, char **tab)
{
    if (line[pas->i + 1] == '!') {
        assign_tab(buff, tab, &pas->index, &pas->ind);
        buff = malloc(sizeof(char) * strlen(line));
        pas->sep = 0;
        return 1;
    }
    if (pas->sep == 1 && verif_sep(line[pas->i]) == 1) {
        assign_tab(buff, tab, &pas->index, &pas->ind);
        buff = malloc(sizeof(char) * strlen(line));
        pas->sep = 0;
    }
    return 0;
}

char **gen_tab_line(char *line)
{
    char **tab = caloc_array(4);
    char *buff = malloc(sizeof(char) * strlen(line) + 1);
    struct passer pas;

    pas.ind = 0;
    pas.index = 0;
    pas.sep = 0;
    for (pas.i = 0; line[pas.i] != '\0'; pas.i++) {
        if (line[pas.i] == '!')
            pas.sep = (pas.sep == 0) ? 1 : 0;
        if (gen_tab_line_cond(line, &pas, buff, tab) == 1)
            continue;
        buff[pas.ind] = line[pas.i];
        pas.ind++;
    }
    assign_tab(buff, tab, &pas.index, &pas.ind);
    tab[pas.index] = NULL;
    return tab;
}

static char *assigne_three(char *line, char **tab)
{
    int ind = get_ind_hist(tab);
    char *new = NULL;

    free(line);
    tab[ind] = find_last_cmd(tab[ind]);
    if (tab[ind] == NULL)
        return NULL;
    new = my_strcat(tab[0], " ");
    new = my_strcat(new, tab[1]);
    new = my_strcat(new, " ");
    new = my_strcat(new, tab[2]);
    return new;
}

static char *assigne_two(char *line, char **tab)
{
    int ind = get_ind_hist(tab);
    char *new = NULL;

    free(line);
    tab[ind] = find_last_cmd(tab[ind]);
    if (tab[ind] == NULL)
        return NULL;
    new = my_strcat(tab[0], " ");
    new = my_strcat(new, tab[1]);
    return new;
}

char *change_line(char *line)
{
    char *new = NULL;
    char **tab = gen_tab_line(line);

    if (tab[1] == NULL) {
        free(line);
        tab[0] = find_last_cmd(tab[0]);
        if (tab[0] == NULL)
            return NULL;
        new = strdup(tab[0]);
    }
    if (tab[1] != NULL && tab[2] == NULL) {
        new = assigne_two(line, tab);
    }
    if (tab[1] != NULL && tab[2] != NULL && tab[3] == NULL) {
        new = assigne_three(line, tab);
    }
    free_array(tab, 0);
    return new;
}
