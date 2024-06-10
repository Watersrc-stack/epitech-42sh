/*
** EPITECH PROJECT, 2024
** mysh2
** File description:
** parse_command
*/

#include "../../include/mysh.h"
#include <string.h>
#include <signal.h>

struct passer {
    int *i;
    int j;
    command_tree_node_t **current;
};

/*static char **separate_comas(char *line)
{
    char **commands = malloc(sizeof(char *) * MAX_ARGS);
    int i = 0;
    char *token = strtok(line, ";");

    while (token != NULL) {
        token = trim_space(token);
        commands[i] = strdup(token);
        token = strtok(NULL, ";");
        i++;
    }
    commands[i] = NULL;
    return commands;
}*/

int add_command(char **args, char **operators, struct passer *passer)
{
    int *i = passer->i;
    int j = passer->j;
    command_tree_node_t **current = passer->current;

    if (strcmp(args[*i], operators[j]) == 0) {
        (*current)->value = strdup(operators[j]);
        (*current)->left = init_tree();
        if (args[*i - 1] == NULL || args[*i + 1] == NULL) {
            printf("Invalid null command.\n");
            return 1;
        }
        (*current)->left->value = strdup(args[*i - 1]);
        (*current)->left->parent = *current;
        (*current)->right = init_tree();
        (*current)->right->value = strdup(args[*i + 1]);
        (*current)->right->parent = *current;
        *current = (*current)->left;
        *i = *i - 1;
    }
    return 0;
}

int scan_operators(char **args, char **operators,
    command_tree_node_t **current, int i)
{
    struct passer passer;
    int return_value = 0;

    for (passer.j = 0; operators[passer.j]; passer.j++) {
        passer.i = &i;
        passer.current = current;
        if (add_command(args, operators, &passer) == 1) {
            return_value = 1;
            break;
        }
    }
    return return_value;
}

int add_commands_to_tree(char *command, command_tree_node_t *root)
{
    char *operators[4] = {"|", "<<", "<", NULL};
    char **args;
    char *command_dup = strdup(command);
    command_tree_node_t *current = root;
    int len;

    args = separate_command(command_dup);
    len = my_arraylen(args);
    free(command_dup);
    for (int i = len - 1; i >= 0; i--) {
        if (scan_operators(args, operators, &current, i) == 1)
            return free_array(args, 1);
    }
    return free_array(args, 0);
}

/*void print_tree(command_tree_node_t *root, int depth, char *side)
 {
     if (root == NULL)
         return;
     for (int i = 0; i < depth; i++)
         printf("\t");
     printf("%s (%s)\n", root->value, side);
     print_tree(root->left, depth + 1, "left");
     print_tree(root->right, depth + 1, "right");
}*/
// removed theses lines from if (redirector_found)
// root->left->value = strdup(command);
// free(root->left->value);
static int create_tree(char *command,
    char ***env, built_commands_t *built_commands)
{
    command_tree_node_t *root = init_tree();
    int redirector_found = search_redirection(command, root);
    int ret = 0;

    if (redirector_found) {
        root->left = init_tree();
        root->left->parent = root;
        root->left->value = strdup(command);
        root = root->left;
    } else if (redirector_found == 0)
        root->value = strdup(command);
    else
        return 84;
    if (add_commands_to_tree(command, root) == 1)
        return 1;
    if (root->parent != NULL)
        root = root->parent;
    ret = execute_tree(root, env, built_commands, 0);
    destroy_tree(root);
    return ret;
}

static int is_empty_or_whitespace(const char *str)
{
    while (*str) {
        if (!is_space((unsigned char)*str))
            return 0;
        str++;
    }
    return 1;
}

static int parse_command_bis(char **commands, int i, int last_return)
{
    if (commands[i + 1] != NULL && strcmp("&&", commands[i + 1]) == 0
        && last_return != 0) {
        return 1;
    }
    if (commands[i + 1] != NULL && strcmp("||", commands[i + 1]) == 0
        && last_return == 0) {
        return 1;
    }
    return 0;
}

int parse_command(char *line, char ***env, built_commands_t *built_commands)
{
    char **commands = my_to_word_array(line, ";&&||");
    int last_return = 0;

    if (is_empty_or_whitespace(line))
        return 0;
    for (int i = 0; commands[i]; i += 2) {
        last_return = create_tree(commands[i], env, built_commands);
        if (commands[i + 1] == NULL ||
        parse_command_bis(commands, i, last_return) != 0)
            break;
    }
    free_array(commands, 0);
    free(line);
    return last_return;
}
