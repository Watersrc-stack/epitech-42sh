/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** env_commands
*/

#include "../../include/mysh.h"

int find_command_line_len(char **args)
{
    int i = 1;
    int len = 0;

    while (args[i]) {
        len += strlen(args[i]);
        len += 1;
        i++;
    }
    len += 1;
    return len;
}

char *create_command_line(char **args)
{
    char *command;
    int i = 1;
    int len = find_command_line_len(args);

    command = malloc(len);
    for (i = 0; i < len; i++)
        command[i] = '\0';
    i = 1;
    while (args[i]) {
        strcat(command, args[i]);
        if (args[i + 1])
            strcat(command, " ");
        i++;
    }
    command[len] = '\0';
    return command;
}

/*
    Env cannot take anything as argument : bonus
*/
int env_command(char **args, char ***env)
{
    char **env_cpy = *env;

    if (args[1] == NULL) {
        for (int i = 0; env_cpy[i]; i++)
            printf("%s\n", env_cpy[i]);
    } else {
        printf("env: Env cannot take args\n");
        return 1;
    }
    return 0;
}
