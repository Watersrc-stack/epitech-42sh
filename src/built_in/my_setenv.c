/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** my_setenv
*/

#include "../../include/mysh.h"

static void cat_value(char *value, char **env, int i)
{
    if (value) {
        strcat(env[i], value);
    }
}

char **change_env(char *name, char *value, char **env)
{
    int i = 0;

    while (env[i]) {
        if (strncmp(env[i], name, strlen(name)) == 0) {
            env[i] =
                malloc(strlen(name) + (value ? strlen(value) : 0) + 2);
            strcpy(env[i], name);
            strcat(env[i], "=");
            cat_value(value, env, i);
        }
        i++;
    }
    return env;
}

char **add_env(char *name, char *value, char **env)
{
    int env_size = 0;
    char **new_env;

    while (env[env_size])
        env_size++;
    new_env = malloc(sizeof(char *) * (env_size + 2));
    for (int i = 0; i < env_size; i++) {
        new_env[i] = env[i];
    }
    new_env[env_size] =
        malloc(strlen(name) + (value ? strlen(value) : 0) + 2);
    strcpy(new_env[env_size], name);
    strcat(new_env[env_size], "=");
    if (value) {
        strcat(new_env[env_size], value);
    }
    new_env[env_size + 1] = NULL;
    return new_env;
}

int set_new_env(char *name, char *value, char ***env)
{
    char *var = my_getenv(name, *env);

    if (var == NULL) {
        *env = add_env(name, value, *env);
    }
    if (var != NULL) {
        *env = change_env(name, value, *env);
    }
    return 0;
}

static int setenv_usage(char **args)
{
    if (strcmp(args[1], "-h") == 0) {
        printf("Usage: setenv NAME VALUE [OVERWRITE]\n");
        return 1;
    }
    return 0;
}

static int my_isalphanumeric(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] < '0' || (str[i] > '9' && str[i] < 'A') ||
            (str[i] > 'Z' && str[i] < 'a') || str[i] > 'z')
            return 0;
    }
    return 1;
}

int no_args_or_help(int args_nbr, char **args, char ***env)
{
    if (args_nbr == 0) {
        env_command(args, env);
        return 1;
    }
    if (setenv_usage(args))
        return 1;
    return 0;
}

int setenv_command(char **args, char ***env)
{
    int i = 1;
    int args_nbr = 0;

    while (args[i]) {
        i++;
        args_nbr++;
    }
    if (no_args_or_help(args_nbr, args, env))
        return 0;
    if (args_nbr == 1 || args_nbr == 2) {
        if (!my_isalphanumeric(args[1])) {
            printf("setenv: Variable name must ");
            printf("contain alphanumeric characters.\n");
            return 0;
        }
        set_new_env(args[1], args[2], env);
    } else
        printf("setenv: Invalid arguments, -h for usage.\n");
    return 0;
}
