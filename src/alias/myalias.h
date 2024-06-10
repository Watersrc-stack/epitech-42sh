/*
** EPITECH PROJECT, 2023
** B-PSU-200-MPL-2-1-42sh-killian.cassard
** File description:
** alias.h
*/

#pragma once
#include "../../include/mysh.h"

typedef struct alias_s {
    char *name;
    char *value;
    struct alias_s *next;
} alias_t;

typedef struct global_alias_s {
    alias_t *alias;
} global_alias_t;

global_alias_t *alias_struct(void);
int pars_alias(char **arg);
char *get_alias(char *name);
int is_alias(char *name);
int unalias(char **arg);
