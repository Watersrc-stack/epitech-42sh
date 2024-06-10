/*
** EPITECH PROJECT, 2023
** B-PSU-200-MPL-2-1-42sh-killian.cassard
** File description:
** inhibitors.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

// This function shifts the string from the start index
// to the end of the string
// used after finding a backslash character
void shift_str(char *str, int start)
{
    int i = start;

    for (; str[i] != '\0'; i++)
        str[i] = str[i + 1];
    str[i] = '\0';
}

// shrink the string by inhibitors
void shrink_str(char *str)
{
    if (str == NULL)
        return;
    if (strlen(str) == 0)
        return;
    if (str[strlen(str) - 1] == '\\')
        str[strlen(str) - 1] = '\0';
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == '\\')
            shift_str(str, i);
}

static void update_quotes(bool *in_quote, char *quote, char *str, int i)
{
    if (*in_quote == false){
        *in_quote = true;
        *quote = str[i];
    } else if (*quote == str[i]){
        *in_quote = false;
        *quote = '\0';
    }
}

// get the length of the array by spaces
int get_len(char *str)
{
    int len = 0;
    bool in_quote = false;
    char quote = '\0';

    if (str[strlen(str) - 1] == '\\')
        str[strlen(str) - 1] = '\0';
    for (int i = 0; str[i] != '\0'; i++){
        if (str[i] == '\\'){
            i++;
            continue;
        }
        if (str[i] == '\'' || str[i] == '\"')
            update_quotes(&in_quote, &quote, str, i);
        if ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
            && in_quote == false)
            len++;
    }
    return len + 1;
}

// equivalent to strtok, but in one time only
void cut_str(char *str)
{
    int slen = strlen(str);
    bool in_quote = false;
    char quote = '\0';

    for (int i = 0; i < slen; i++){
        if (str[i] == '\\'){
            i++;
            continue;
        }
        if (str[i] == '\'' || str[i] == '\"')
            update_quotes(&in_quote, &quote, str, i);
        if ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        && in_quote == false)
            str[i] = '\0';
    }
}

static bool quotes_error_handling(char *str)
{
    bool in_quote = false;
    char quote = '\0';

    for (int i = 0; str[i] != '\0'; i++){
        if (str[i] == '\'' || str[i] == '\"')
            update_quotes(&in_quote, &quote, str, i);
    }
    if (in_quote == true)
        printf("Unmatched '%c'.\n", quote);
    return in_quote;
}

static void check_array(char **array, int i)
{
    if (array[i][0] == '"' || array[i][0] == '\''){
        shift_str(array[i], 0);
        array[i][strlen(array[i]) - 1] = '\0';
    }
    if (array[i][strlen(array[i]) - 1] == '"' ||
        array[i][strlen(array[i]) - 1] == '\'')
        array[i][strlen(array[i]) - 1] = '\0';
}

// static int arrlen(char **array)
// {
//     int i = 0;

//     for (; array[i] != NULL; i++);
//     return i;
// }

// shrink the string by inhibitors,
// resize array if last is empty
void finalize(char **array, int len, int letters)
{
    for (int i = 0; array[i] != NULL; i++)
        shrink_str(array[i]);
    for (int i = 0; array[len - 1][i] != '\0'; i++)
        if (!(array[len - 1][i] == ' ' || array[len - 1][i] == '\t' ||
            array[len - 1][i] == '\n'))
            letters++;
    if (letters == 0){
        free(array[len - 1]);
        array[len - 1] = NULL;
    }
    for (int i = 0; array[i] != NULL; i++){
        if (quotes_error_handling(array[i])){
            free(array[0]);
            array[0] = strdup(" 0xdeadbeef");
        }
        check_array(array, i);
    }
}
