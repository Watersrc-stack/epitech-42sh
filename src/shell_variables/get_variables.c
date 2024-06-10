/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-42sh-killian.cassard [WSL: Ubuntu-24.04]
** File description:
** get_variables
*/

#include "../../include/mysh.h"
#include "shell_variables.h"
#include <stdio.h>

int set_command(char **args, char ***env)
{
    env = env;
    if (args[1] == NULL) {
        display_vars();
        return 0;
    }
    create_var(args[1], args[2]);
    return 0;
}

char *get_var_value(char *name)
{
    var_t *tmp = var_struct()->var;

    while (tmp) {
        if (strcmp(tmp->name, name) == 0)
            return tmp->value;
        tmp = tmp->next;
    }
    return '\0';
}

char *get_var_word(char *str)
{
    char *word;
    int i = 0;

    for (i = 0; str[i] && str[i] != ' '; i++);
    word = malloc(sizeof(char) * (i + 1));
    if (!word)
        return NULL;
    for (i = 0; str[i] && str[i] != ' '; i++)
        word[i] = str[i];
    word[i - 1] = '\0';
    return word;
}
