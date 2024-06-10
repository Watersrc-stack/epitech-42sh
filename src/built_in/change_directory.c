/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** commands
*/

#include "../../include/mysh.h"
#include <string.h>

/*
    Could use improvements :
    - When we go back (..), instead of adding ".." to the current directory,
    we could remove the last directory from the current directory.
*/

char **add_oldpwd(char **env, char *old_dir)
{
    int env_size = 0;
    char **new_env;

    while (env[env_size])
        env_size++;
    new_env = malloc(sizeof(char *) * (env_size + 2));
    for (int i = 0; i < env_size; i++) {
        new_env[i] = env[i];
    }
    new_env[env_size] = malloc(strlen("OLDPWD=") + strlen(old_dir) + 1);
    strcpy(new_env[env_size], "OLDPWD=");
    strcat(new_env[env_size], old_dir);
    new_env[env_size + 1] = NULL;
    return new_env;
}

static void change_wd(char ***env, char *new_dir, char *old_dir)
{
    int len_old = (strlen("OLDPWD=") + strlen(old_dir) + 1);
    int len_new = (strlen("PWD=") + strlen(new_dir) + 1);

    if (my_getenv("OLDPWD", *env) == NULL) {
        *env = add_oldpwd(*env, old_dir);
    }
    for (int i = 0; (*env)[i]; i++) {
        if (strncmp((*env)[i], "OLDPWD=", 7) == 0) {
            (*env)[i] = malloc(sizeof(char) * len_old);
            strcpy((*env)[i], "OLDPWD=");
            strcat((*env)[i], old_dir);
        }
        if (strncmp((*env)[i], "PWD=", 4) == 0) {
            (*env)[i] = malloc(sizeof(char) * len_new);
            strcpy((*env)[i], "PWD=");
            strcat((*env)[i], new_dir);
        }
    }
}

char *create_new_wd(char *old_wd, char *arg)
{
    char *new_wd = malloc(strlen(old_wd) + strlen(arg) + 2);

    strcpy(new_wd, old_wd);
    strcat(new_wd, "/");
    strcat(new_wd, arg);
    return new_wd;
}

int file_not_found(char *arg)
{
    if (chdir(arg) != 0) {
        printf("%s: Not a directory.\n", arg);
        return 1;
    }
    return 0;
}

int back_to_old_wd(char ***env, char *home, char *cwd)
{
    char *old_wd;
    char *old_dir;

    old_wd = my_getenv("OLDPWD", *env);
    old_dir = strtok(old_wd, "=");
    chdir(home);
    chdir(old_dir);
    cwd = my_getenv("PWD", *env);
    change_wd(env, old_wd, cwd);
    return 0;
}

static int handle_dash_arg(int first_cycle, char **args, char ***env)
{
    char *cwd = my_getenv("PWD", *env);
    char *home = my_getenv("HOME", *env);

    if (strcmp(args[1], "-") == 0) {
        if (first_cycle == 0) {
            printf(": No such file or directory.\n");
            return 2;
        }
        back_to_old_wd(env, home, cwd);
        return 1;
    }
    return 0;
}

int cd_command(char **args, char ***env)
{
    char *cwd = my_getenv("PWD", *env);
    char *home = my_getenv("HOME", *env);
    static int first_cycle = 0;
    int back_returned;

    if (args[1] == NULL) {
        chdir(home);
        change_wd(env, home, cwd);
        first_cycle++;
        return 0;
    }
    back_returned = handle_dash_arg(first_cycle, args, env);
    if (back_returned != 0)
        return back_returned - 1;
    if (file_not_found(args[1]))
        return 1;
    change_wd(env, create_new_wd(cwd, args[1]), cwd);
    first_cycle = 1;
    return 0;
}
