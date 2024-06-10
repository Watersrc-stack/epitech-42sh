/*
** EPITECH PROJECT, 2024
** kehnsh
** File description:
** initialise_history.c
*/

#include "../../../include/mysh.h"

char *get_hist_value(char *buff, int st)
{
    char *val = malloc(sizeof(char) * (get_size_his(buff, st) + 1));
    int ind = 0;

    for (int i = 0; buff[i] != '\0'; i++) {
        if (st > 0 && (buff[i] == ' ' || buff[i] == ':')) {
            st--;
            continue;
        }
        if (st > 0)
            continue;
        val[ind] = buff[i];
        ind++;
    }
    val[ind] = '\0';
    return val;
}

int hist_i(char *buff, int st)
{
    int nb = 0;

    for (int i = 0; buff[i] != '\0'; i++) {
        if (st > 0 && (buff[i] == ' ' || buff[i] == ':')) {
            st--;
            continue;
        }
        if (st > 0)
            continue;
        if (buff[i] == ' ' || buff[i] == ':')
            break;
        if (buff[i] >= '0' && buff[i] <= '9')
            nb = nb * 10 + (buff[i] - '0');
    }
    return nb;
}

char *get_hist_command_by_id(int id)
{
    history_t *tmp = hist()->history;

    for (int i = 0; i < id; i++)
        tmp = tmp->next;
    return tmp->cmd;
}

int get_length_hist(void)
{
    history_t *tmp = hist()->history;
    int i = 0;

    if (!tmp)
        return 0;
    while (tmp) {
        i++;
        tmp = tmp->next;
    }
    return i;
}
