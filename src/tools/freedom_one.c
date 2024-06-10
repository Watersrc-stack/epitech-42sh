/*
** EPITECH PROJECT, 2023
** B-PSU-200-MPL-2-1-42sh-killian.cassard
** File description:
** freedom_one.c
*/

#include "../../include/mysh.h"

void destroy_tree(command_tree_node_t *root)
{
    if (root->left != NULL)
        destroy_tree(root->left);
    if (root->right != NULL)
        destroy_tree(root->right);
    if (root->value != NULL)
        free(root->value);
    if (root != NULL)
        free(root);
}

int pars_alias_wrapper(char **arg)
{
    int ret = pars_alias(arg);

    free_array(arg, 0);
    return ret;
}

int built_commands_wrapper(built_commands_t *built_commands,
    int i, char **args, char ***env)
{
    int ret = built_commands[i].func(args, env);

    free_array(args, 0);
    return ret;
}

int exec_bin_wrapper(char **args, char **env, bool system)
{
    int ret = exec_bin(args, env, system);

    free_array(args, 0);
    return ret;
}
