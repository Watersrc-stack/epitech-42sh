/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** str_to_word_array
*/

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../../include/mysh.h"

// this function replaces the original string_to_array function
// I remade it, more simply and more efficient because
// the function is called only once in the whole program
// The addon is that it can handle the backslash character
char **string_to_array(char *src)
{
    char *cpy = strdup(src);
    char *ptr = cpy;
    int len = get_len(cpy);
    char **array = malloc(sizeof(char *) * (len + 1));
    int letters = 0;

    cut_str(cpy);
    for (int i = 0; i < len; i++) {
        array[i] = strdup(cpy);
        while (*cpy != '\0')
            cpy++;
        cpy++;
    }
    free(ptr);
    array[len] = NULL;
    finalize(array, len, letters);
    return array;
}
