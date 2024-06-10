/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** my_unsetenv
*/

#include "../../include/mysh.h"

char **remove_env(char *name, char **env)
{
    int i = 0;
    int j = 0;
    int env_size = 0;
    char **new_env;

    while (env[env_size])
        env_size++;
    new_env = malloc(sizeof(char *) * env_size);
    while (env[i]) {
        if (strncmp(env[i], name, strlen(name)) != 0) {
            new_env[j] = env[i];
            j++;
        }
        i++;
    }
    new_env[j] = NULL;
    return new_env;
}

int unset_env(char *name, char ***env)
{
    if (my_getenv(name, *env) == NULL) {
        printf("unsetenv: Variable does not exist.\n");
        return 1;
    }
    *env = remove_env(name, *env);
    return 0;
}

int unsetenv_usage(char **args)
{
    if (strcmp(args[1], "-h") == 0) {
        printf("Usage: unsetenv NAME\n");
        return 1;
    }
    return 0;
}

int unsetenv_command(char **args, char ***env)
{
    int i = 1;
    int args_nbr = 0;

    if (unsetenv_usage(args))
        return 0;
    while (args[i]) {
        i++;
        args_nbr++;
    }
    if (args_nbr == 1) {
        if (unset_env(args[1], env) == 1)
            return 1;
    } else {
        printf("unsetenv: Invalid arguments, -h for usage.\n");
        return 1;
    }
    return 0;
}
