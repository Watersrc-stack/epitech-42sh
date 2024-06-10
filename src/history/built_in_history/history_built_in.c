/*
** EPITECH PROJECT, 2024
** kehnsh
** File description:
** initialise_history.c
*/

#include "../../../include/mysh.h"

int is_num(char *string)
{
    for (int i = 0; string[i] != '\0'; i++) {
        if (!(string[i] >= '0' && string[i] <= '9'))
            return 1;
    }
    return 0;
}

int history_command(char **args, char ***env)
{
    (void)env;
    if (args[1] != NULL && is_num(args[1]) != 0) {
        write(2, "history: Badly formed number.\n", 30);
        return 1;
    }
    if (args[1] == NULL)
        print_all_history();
    else {
        print_history(atoi(args[1]));
    }
    return 0;
}
