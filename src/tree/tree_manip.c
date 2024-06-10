/*
** EPITECH PROJECT, 2024
** mysh2
** File description:
** tree_manip
*/

#include "../../include/mysh.h"

command_tree_node_t *init_tree(void)
{
    command_tree_node_t *root = malloc(sizeof(command_tree_node_t));

    root->value = NULL;
    root->left = NULL;
    root->right = NULL;
    root->parent = NULL;
    return root;
}

void add_node(command_tree_node_t *current, char *value)
{
    current->value = strdup(value);
    current->left = init_tree();
    current->left->parent = current;
    current->right = init_tree();
    current->right->parent = current;
}
