/*
** EPITECH PROJECT, 2024
** kehnsh
** File description:
** get_info.c
*/

#include "../../../include/mysh.h"

history_t *hist_node(int num, int h, int m, char *val)
{
    history_t *new = malloc(sizeof(history_t));

    new->command_index = num;
    new->hours = h;
    new->minutes = m;
    new->cmd = strdup(val);
    new->next = NULL;
    return new;
}

void hist_back(history_t *new, history_t **head)
{
    history_t *tmp = *head;

    if (*head == NULL) {
        *head = new;
        return;
    }
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = new;
}

int last_i(history_t *history)
{
    if (history == NULL)
        return 1;
    return history->command_index + 1;
}

void hist_front(history_t *new, history_t **head)
{
    if (*head == NULL) {
        *head = new;
        return;
    }
    new->next = *head;
    *head = new;
}
