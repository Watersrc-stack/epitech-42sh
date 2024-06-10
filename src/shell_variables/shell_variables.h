/*
** EPITECH PROJECT, 2024
** B-PSU-200-MPL-2-1-42sh-killian.cassard [WSL: Ubuntu-22.04]
** File description:
** shell_variables
*/

#pragma once

#include "../../include/mysh.h"

typedef struct var_s {
    char *name;
    char *value;
    struct var_s *next;
} var_t;

typedef struct args_s {
    char *name;
    char *value;
    int len;
} args_t;

typedef struct global_var_s {
    var_t *var;
} global_var_t;

global_var_t *var_struct(void);
int set_command(char **args, char ***env);
void display_vars(void);
void create_var(char *name, char *value);
char *replace_variables(char *command);
char *get_var_value(char *name);
char *get_var_word(char *str);
