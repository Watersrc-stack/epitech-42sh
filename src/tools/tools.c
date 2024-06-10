/*
** EPITECH PROJECT, 2024
** mysh2
** File description:
** tools
*/

#include "../../include/mysh.h"
#include <string.h>
#include <signal.h>

int is_space(char c)
{
    return c == ' ' || c == '\t' || c == '\n'
        || c == '\v' || c == '\f' || c == '\r';
}

static void trim_space2(char *str, char *result, char *prev, int *count)
{
    if (!is_space(*str) ||
    (is_space(*str) && !is_space(*prev) && *count > 0)) {
        result[*count] = is_space(*str) ? ' ' : *str;
        *prev = *str;
        (*count)++;
    }
}

char *trim_space(char *str)
{
    char *result = malloc(strlen(str) + 1);
    int count = 0;
    char prev = '\0';

    while (*str) {
        trim_space2(str, result, &prev, &count);
        str++;
    }
    if (count > 0 && result[count - 1] == ' ')
        count--;
    result[count] = '\0';
    return result;
}

void nullize_string(char *str)
{
    for (int i = 0; str[i]; i++)
        str[i] = '\0';
}

int my_arraylen(char **array)
{
    int i = 0;

    for (; array[i]; i++);
    return i;
}

int free_array(char **array, int return_code)
{
    if (array != NULL) {
        for (int i = 0; array[i] != NULL; i++)
            free(array[i]);
        free(array);
    }
    return return_code;
}
