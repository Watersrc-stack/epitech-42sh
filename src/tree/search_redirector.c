/*
** EPITECH PROJECT, 2024
** mysh2
** File description:
** search_redirector
*/

#include "../../include/mysh.h"

struct arg_passer_s {
    char **redirectors;
    int *redirector_found;
    int j;
};

static int add_redirector(char *command, command_tree_node_t *root,
    struct arg_passer_s *passer)
{
    char **args = NULL;
    char **redirectos = passer->redirectors;
    int *redirector_found = passer->redirector_found;
    int j = passer->j;

    if (strncmp(command, redirectos[j], strlen(redirectos[j])) == 0) {
        if (*redirector_found) {
            printf("Ambiguous output redirect.\n");
            return 84;
        }
        args = separate_command(command);
        root->value = strdup(args[0]);
        root->right = init_tree();
        root->right->value = strdup(args[1]);
        root->right->parent = root;
        nullize_string(command);
        *redirector_found = 1;
        free_array(args, 0);
    }
    return 0;
}

static int process_redirector(char *command,
    command_tree_node_t *root, char **redirectors, int *redirector_found)
{
    struct arg_passer_s arg_passer = {redirectors, redirector_found, 0};

    for (int j = 0; redirectors[j]; j++) {
        if (add_redirector(command, root, &arg_passer) == 84)
            return 84;
    }
    return 0;
}

int search_redirection(char *command, command_tree_node_t *root)
{
    int redirector_found = 0;
    char *redirectors[3] = {">", ">>", NULL};

    for (int i = 0; command[i]; i++) {
        if (process_redirector(&command[i], root,
            redirectors, &redirector_found) == 84)
            return 84;
    }
    return redirector_found;
}
