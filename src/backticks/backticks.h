/*
** EPITECH PROJECT, 2023
** B-PSU-200-MPL-2-1-42sh-killian.cassard
** File description:
** backticks.h
*/

#pragma once
#include "../../include/mysh.h"

typedef struct backticks_s {
    char *backticks_command;
    char *result;
    struct backticks_s *next;
} backticks_t;

typedef struct global_backticks_s {
    backticks_t *backticks;
} global_backticks_t;

global_backticks_t *backticks_struct(void);
void check_backticks(char **command, char ***env, built_commands_t *built_cmd);
