/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** my_pas_array
*/

#include "../../include/mysh.h"

struct passer_t {
    char **cmd;
    int i;
    int y;
    int ind;
    char *buff;
};

static char *my_charcat(char a, char b)
{
    char *str = malloc(sizeof(char) * 3);

    str[0] = a;
    str[1] = b;
    str[2] = '\0';
    return str;
}

static char *my_caloc(int size)
{
    char *str = malloc(sizeof(char) * size);

    for (int i = 0; i < size; i++)
        str[i] = '\0';
    return str;
}

static char **end_pas_array(struct passer_t *pas)
{
    pas->cmd[pas->ind] = strdup(pas->buff);
    free(pas->buff);
    pas->cmd[pas->ind + 1] = NULL;
    return pas->cmd;
}

static void reset_var_pas_array(struct passer_t *pas, char *line)
{
    free(pas->buff);
    pas->buff = my_caloc(strlen(line) + 1);
    pas->ind += 2;
    pas->y = 0;
    if (line[pas->i + 1] == ' ')
            pas->i += 1;
}

int to_pas_array_bis(char *line, struct passer_t *pas, char *separator)
{
    if ((line[pas->i] == separator[1] && line[pas->i + 1] == separator[2]) ||
        (line[pas->i] == separator[3] && line[pas->i + 1] == separator[4])) {
        pas->cmd[pas->ind] = strdup(pas->buff);
        pas->cmd[pas->ind + 1] = strdup(my_charcat(line[pas->i],
                                                        line[pas->i + 1]));
        pas->i += 1;
        reset_var_pas_array(pas, line);
        return 1;
    }
    if (line[pas->i] == separator[0]) {
        pas->cmd[pas->ind] = strdup(pas->buff);
        pas->cmd[pas->ind + 1] = strdup(";");
        reset_var_pas_array(pas, line);
        return 1;
    }
    return 0;
}

char **my_to_word_array(char *line, char *separator)
{
    struct passer_t pas;
    int ind = 0;

    pas.buff = my_caloc(strlen(line) + 1);
    pas.y = 0;
    pas.ind = 0;
    pas.cmd = malloc(sizeof(char *) * MAX_ARGS);
    for (pas.i = 0; line[pas.i] != '\0'; pas.i++) {
        if (line[pas.i] != ' ')
            ind = 1;
        if (line[pas.i] == ' ' && ind == 0)
            continue;
        if (line[pas.i] == ' ' && line[pas.i + 1] == ' ')
            continue;
        if (to_pas_array_bis(line, &pas, separator) == 1)
            continue;
        pas.buff[pas.y] = line[pas.i];
        pas.y++;
    }
    return end_pas_array(&pas);
}
