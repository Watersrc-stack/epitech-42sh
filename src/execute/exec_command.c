/*
** EPITECH PROJECT, 2024
** mysh2
** File description:
** exec_command
*/

#include "../../include/mysh.h"
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

static int exec_system_bin_next(char **args, char *path, char **env, char *dup)
{
    char *dir = strtok(dup, ":");

    while (dir != NULL) {
        path = malloc(strlen(dir) + strlen("/")
                + strlen(args[0]) + 1);
        strcpy(path, dir);
        strcat(path, "/");
        strcat(path, args[0]);
        execve(path, args, env);
        free(path);
        dir = strtok(NULL, ":");
    }
    free(dup);
    return 0;
}

int exec_system_bin(char **args, char *path, char **env)
{
    char *path_env = my_getenv("PATH", env);
    char *path_env_dup = NULL;

    if (path_env != NULL) {
        path_env_dup = strdup(path_env);
        exec_system_bin_next(args, path, env, path_env_dup);
    } else {
        path_env_dup = my_strcat("/bin/", args[0]);
        execve(path_env_dup, args, env);
        free(path_env_dup);
        return 0;
    }
    return 0;
}

static void handle_signal_status(int status)
{
    if (WTERMSIG(status) == SIGSEGV)
        printf("Segmentation fault");
    if (WTERMSIG(status) == SIGINT)
        printf("Interrupt");
    if (WTERMSIG(status) == SIGABRT)
        printf("Aborted");
    if (WTERMSIG(status) == SIGFPE)
        printf("Floating exception");
    if (WTERMSIG(status) == SIGILL)
        printf("Illegal instruction");
    if (WTERMSIG(status) == SIGTERM)
        printf("Terminated");
    if (WCOREDUMP(status))
        printf(" (core dumped)");
    printf("\n");
}

static int handle_exit(int status)
{
    if (status == 3328 || status == 2048) {
        return 1;
    }
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    if (WIFSIGNALED(status)) {
        handle_signal_status(status);
        return 128 + WTERMSIG(status);
    }
    if (!WIFEXITED(status) && !WIFSIGNALED(status))
        return -1;
    return 0;
}

static void print_exec_error(int function_return, char **args)
{
    if (function_return == EACCES) {
        printf("%s: Permission denied.\n", args[0]);
    }
    if (function_return == ENOEXEC) {
        printf("%s: Exec format error. Wrong Architecture.\n", args[0]);
    }
}

int exec_locale_or_system(char **args, char *path, char **env, bool system)
{
    int function_return = -1;

    if (system) {
        exec_system_bin(args, path, env);
    } else {
        if (execve(args[0], args, env) == -1) {
            function_return = errno;
            print_exec_error(function_return, args);
            exit(function_return);
        }
    }
    printf("%s: Command not found.\n", args[0]);
    exit(1);
    return 0;
}

int exec_bin(char **args, char **env, bool system)
{
    pid_t pid = fork();
    char *path = NULL;
    int function_return = -1;
    int status;

    if (pid == 0) {
        return exec_locale_or_system(args, path, env, system);
    } else {
        waitpid(pid, &status, 0);
        return handle_exit(status);
    }
    return function_return;
}

int command_is_dir(char *command)
{
    for (int i = 0; command[i]; i++) {
        if (command[i] == '/')
            return 1;
        if (command[i] == ' ')
            return 0;
    }
    return 0;
}

int exec_command(char *command, char ***env, built_commands_t *built_commands)
{
    char **args = string_to_array(command);
    int function_return = -1;

    if (args == NULL || args[0] == NULL || strcmp(args[0], " 0xdeadbeef") == 0)
        return free_array(args, 0);
    if (strcmp(args[0], "alias") == 0 || strcmp(args[0], "unalias") == 0)
        return pars_alias(args);
    if (is_alias(args[0]))
        return execute_alias(args, env, built_commands);
    for (int i = 0; built_commands[i].name; i++) {
        if (strcmp(built_commands[i].name, args[0]) == 0)
            return built_commands_wrapper(built_commands, i, args, env);
    }
    if (command_is_dir(command))
        return exec_bin_wrapper(args, *env, false);
    else
        return exec_bin_wrapper(args, *env, true);
    free_array(args, 0);
    args = NULL;
    return function_return;
}
