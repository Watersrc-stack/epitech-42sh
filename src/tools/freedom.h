/*
** EPITECH PROJECT, 2023
** B-PSU-200-MPL-2-1-42sh-killian.cassard
** File description:
** freedom.h
*/

#pragma once

#include "../../include/mysh.h"

void destroy_tree(command_tree_node_t *root);
int pars_alias_wrapper(char **arg);

int built_commands_wrapper(built_commands_t *built_commands,
    int i, char **args, char ***env);
int exec_bin_wrapper(char **args, char **env, bool system);
