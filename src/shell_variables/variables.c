/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-42sh-killian.cassard [WSL: Ubuntu-24.04]
** File description:
** variables
*/

/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-42sh-killian.cassard [WSL: Ubuntu-22.04]
** File description:
** variables
*/

#include "../../include/mysh.h"
#include "shell_variables.h"
#include <stdio.h>

global_var_t *var_struct(void)
{
    static global_var_t body = {
        .var = NULL
    };

    body = body;
    return &body;
}

static int check_var_name(char *name, var_t *vars, char *value)
{
    var_t *tmp = vars;

    while (tmp) {
        if (strcmp(tmp->name, name) == 0) {
            tmp->value = strdup(value);
            return 0;
        }
        tmp = tmp->next;
    }
    return 1;
}

void create_var(char *name, char *value)
{
    var_t *new_var = malloc(sizeof(var_t));
    var_t *tmp = var_struct()->var;

    if (!new_var)
        return;
    new_var->name = strdup(name);
    if (value)
        new_var->value = strdup(value);
    else
        new_var->value = "\0";
    new_var->next = NULL;
    if (!tmp) {
        var_struct()->var = new_var;
        return;
    }
    if (check_var_name(name, tmp, value) == 0)
        return;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_var;
}

void display_vars(void)
{
    var_t *tmp = var_struct()->var;

    while (tmp) {
        printf("%s", tmp->name);
        if (tmp->value)
            printf(" %s", tmp->value);
        printf("\n");
        tmp = tmp->next;
    }
}

static bool get_new_len(char *command, int *i, args_t *args)
{
    if (command[*i] == '$') {
        args->name = get_var_word(command + *i + 1);
        args->value = get_var_value(args->name);
        if (!args->value) {
            fprintf(stderr, "%s: Undefined variable.\n", args->name);
            args->len = 0;
            return false;
        }
        args->len += strlen(args->value);
        *i += strlen(args->name);
    } else {
        args->len++;
    }
    return true;
}

static int calcul_new_len(char *command)
{
    args_t *args = malloc(sizeof(args_t));
    bool running = true;

    args->len = 0;
    for (int i = 0; command[i]; i++) {
        running = get_new_len(command, &i, args);
        if (!running)
            return (0);
    }
    return (args->len);
}

static void find_dollar(char *command, int *i, int *j, char **new_command)
{
    char *name;
    char *value;

    name = get_var_word(command + *i + 1);
    value = get_var_value(name);
    for (int k = 0; value[k]; k++) {
        (*new_command)[*j] = value[k];
        *j += 1;
    }
    *i += strlen(name);
    free(name);
}

static char *rewrite_input(char *command)
{
    int j = 0;
    char *new_command = malloc(sizeof(char) * (calcul_new_len(command) + 1));

    for (int i = 0; command[i]; i++) {
        if (command[i] == '$') {
            find_dollar(command, &i, &j, &new_command);
        } else {
            new_command[j] = command[i];
            j++;
        }
    }
    new_command[j] = '\0';
    return new_command;
}

char *replace_variables(char *command)
{
    char *new_command = NULL;
    int new_len = 0;

    new_len = calcul_new_len(command);
    if (new_len == 0)
        return NULL;
    new_command = malloc(sizeof(char) * (new_len + 1));
    if (!new_command)
        return NULL;
    new_command = rewrite_input(command);
    if (new_command == NULL)
        return command;
    return new_command;
}
