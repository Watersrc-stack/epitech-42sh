/*
** EPITECH PROJECT, 2024
** mysh2
** File description:
** separate_command
*/

#include "../../include/mysh.h"

char *operators[] = {"|", ">>", ">", "<", NULL};

void process_arg(char **start, char **end, char **args, int *i)
{
    if (*end != *start) {
        **end = '\0';
        args[*i] = trim_space(*start);
        (*i)++;
    }
}

void process_operator(char **start, char **end, char **args, int *i)
{
    for (int j = 0; operators[j]; j++) {
        if (strncmp(*end, operators[j], strlen(operators[j])) == 0) {
            process_arg(start, end, args, i);
            args[*i] = strdup(operators[j]);
            (*i)++;
            *start = *end + strlen(operators[j]);
            *end = *start;
            return;
        }
    }
    (*end)++;
}

char **separate_command(char *line)
{
    char **args = malloc(sizeof(char *) * MAX_ARGS);
    int i = 0;
    char *start = line;
    char *end = line;
    char *trim = NULL;

    while (*end != '\0') {
        process_operator(&start, &end, args, &i);
    }
    if (end != start) {
        trim = trim_space(start);
        args[i] = strdup(trim);
        free(trim);
        i++;
    }
    args[i] = NULL;
    return args;
}
