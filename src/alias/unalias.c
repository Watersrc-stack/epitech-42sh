/*
** EPITECH PROJECT, 2023
** B-PSU-200-MPL-2-1-42sh-killian.cassard
** File description:
** unalias.c
*/

#include "../../include/mysh.h"
#include "myalias.h"

int del_alias(alias_t *tmp, alias_t *prev, char **arg, int i)
{
    if (strcmp(tmp->name, arg[i]) == 0) {
        if (prev == NULL) {
            alias_struct()->alias = tmp->next;
        } else {
            prev->next = tmp->next;
        }
        free(tmp->name);
        free(tmp->value);
        free(tmp);
        return 1;
    }
    return 0;
}

void check_name_alias(alias_t *tmp, alias_t *prev, char **arg, int i)
{
    while (tmp != NULL) {
        if (del_alias(tmp, prev, arg, i) == 1)
            break;
        prev = tmp;
        tmp = tmp->next;
    }
}

int unalias(char **arg)
{
    alias_t *tmp;
    alias_t *prev;

    for (int i = 1; arg[i]; i++) {
        tmp = alias_struct()->alias;
        prev = NULL;
        check_name_alias(tmp, prev, arg, i);
    }
    return 0;
}
