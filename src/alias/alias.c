/*
** EPITECH PROJECT, 2023
** B-PSU-200-MPL-2-1-42sh-killian.cassard
** File description:
** alias.c
*/

#include "../../include/mysh.h"
#include "myalias.h"

global_alias_t *alias_struct(void)
{
    static global_alias_t body = {
        .alias = NULL
    };

    body = body;
    return &body;
}

static char *get_value(char **arg)
{
    int total_length = 0;
    int current_pos = 0;
    char *result;

    for (int i = 0; arg[i] != NULL; i++) {
        total_length += strlen(arg[i]);
    }
    result = malloc(sizeof(char *) * (total_length + 1));
    if (result == NULL) {
        return NULL;
    }
    for (int i = 2; arg[i] != NULL; i++) {
        strcpy(result + current_pos, arg[i]);
        current_pos += strlen(arg[i]);
        if (arg[i + 1] != NULL) {
            result[current_pos] = ' ';
            current_pos++;
        }
    }
    return result;
}

static int check_alias(alias_t *tmp, char **arg, alias_t *new_alias)
{
    while (tmp != NULL) {
        if (strcmp(tmp->name, arg[1]) == 0) {
            free(new_alias->name);
            free(new_alias->value);
            tmp->value = get_value(arg);
            free(new_alias);
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

static void add_alias(char **arg)
{
    alias_t *new_alias = (alias_t *)malloc(sizeof(alias_t));
    alias_t *tmp = alias_struct()->alias;

    if (new_alias == NULL)
        return;
    new_alias->name = strdup(arg[1]);
    new_alias->value = get_value(arg);
    new_alias->next = NULL;
    if (tmp == NULL) {
        alias_struct()->alias = new_alias;
        return;
    }
    if (check_alias(tmp, arg, new_alias) == 1)
        return;
    tmp = alias_struct()->alias;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new_alias;
}

int is_alias(char *name)
{
    alias_t *tmp = alias_struct()->alias;

    while (tmp != NULL) {
        if (strcmp(tmp->name, name) == 0) {
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

char *get_alias(char *name)
{
    alias_t *tmp = alias_struct()->alias;

    while (tmp != NULL) {
        if (strcmp(tmp->name, name) == 0) {
            return tmp->value;
        }
        tmp = tmp->next;
    }
    return NULL;
}

static void print_alias(void)
{
    alias_t *tmp = alias_struct()->alias;

    while (tmp != NULL) {
        printf("%s\t(%s)\n", tmp->name, tmp->value);
        tmp = tmp->next;
    }
}

static int is_alias_loop(char *name, char *first_name)
{
    if (is_alias(name)) {
        if (strcmp(get_alias(name), first_name) == 0) {
            return 1;
        }
        return is_alias_loop(get_alias(name), first_name);
    }
    return 0;
}

int execute_alias(char **args, char ***env, built_commands_t *built_commands)
{
    if (!is_alias_loop(args[0], args[0])) {
        return exec_command(get_alias(args[0]), env, built_commands);
    } else {
        printf("Alias loop.\n");
        return 1;
    }
}

int pars_alias(char **arg)
{
    if (strcmp(arg[0], "unalias") == 0) {
        if (arg[1] != NULL)
            return unalias(arg);
        return 0;
    }
    if (arg[1] != NULL && strcmp(arg[1], "alias") == 0) {
        printf("%s: Too dangerous to alias that.\n", arg[1]);
        return 0;
    }
    if (arg[1] == NULL) {
        print_alias();
    } else if (arg[1] != NULL && arg[2] != NULL) {
        add_alias(arg);
    }
    return 0;
}
