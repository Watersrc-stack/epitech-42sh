/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** mysh
*/

#include "../include/mysh.h"
#include "../src/backticks/backticks.h"
#include "line_edition/line_edition.h"
#include <string.h>
#include <signal.h>

static built_commands_t *get_commands(void)
{
    static built_commands_t commands[] =
    {
        {"cd", cd_command},
        {"setenv", setenv_command},
        {"unsetenv", unsetenv_command},
        {"env", env_command},
        {"history", history_command},
        {"set", set_command},
        {NULL, NULL}
    };

    return commands;
}

int handle_line(char *line,
    char ***env, built_commands_t *builtin_commands)
{
    static int rv = 0;

    if (strcmp("exit", line) == 0) {
        free(line);
        save_history(*env, 0, 0);
    }
    hist()->dup = strdup(line);
    if (line != NULL && strlen(line) > 0) {
        hist()->dup = verif_hist(hist()->dup);
        if (hist()->dup != NULL) {
            line = re_assigne_line(hist()->dup, line);
            add_history(line);
            rv = parse_command(line, env, builtin_commands);
        } else {
            free(hist()->dup);
            return 1;
        }
    }
    free(hist()->dup);
    return rv;
}

static void clean_scan(char *scan, ssize_t read)
{
    for (int i = 0; i < read; i++) {
        if (scan[i] == '\t')
            scan[i] = ' ';
        if (scan[i] == '\n')
            scan[i] = '\0';
    }
}

static int pipe_mode(char ***env, built_commands_t *builtin_commands)
{
    char *line = NULL;
    ssize_t read;
    size_t len = 0;
    int last_return = 0;

    while (1) {
        read = getline(&line, &len, stdin);
        if (read != -1)
            clean_scan(line, read);
        if (read == -1 || strcmp("exit", line) == 0) {
            free(line);
            save_history(*env, last_return, 1);
        }
        last_return = handle_line(line, env, builtin_commands);
    }
    free(line);
    return last_return;
}

void print_path(void)
{
    printf("%s", getcwd(NULL, 0));
    printf("$> ");
    fflush(stdout);
}

static int tty_mode(char ***env, built_commands_t *builtin_commands)
{
    char *line = NULL;
    ssize_t read;
    static int last_return;

    while (1) {
        print_path();
        line = line_edition();
        read = strlen(line);
        check_backticks(&line, env, builtin_commands);
        line = replace_variables(line);
        if (read != -1)
            clean_scan(line, read);
        if (read == -1)
            save_history(*env, last_return, 0);
        last_return = handle_line(line, env, builtin_commands);
        line_struct()->line = NULL;
    }
    free(line);
    return last_return;
}

int args_mode(int argc, char **argv,
    char ***env, built_commands_t *builtin_commands)
{
    int last_return = 0;
    char **arg = get_arg_script(argv[1]);

    (void)argc;
    for (int i = 1; arg[i] != NULL; i++) {
        last_return = parse_command(arg[i], env, builtin_commands);
    }
    return last_return;
}

int main(int argc, char **argv, char **env)
{
    built_commands_t *builtin_commands = get_commands();
    int last_return = 0;

    intilize_hist(env);
    enable_raw_mode();
    if (argc == 1 && isatty(STDIN_FILENO)) {
        return tty_mode(&env, builtin_commands);
    }
    if (argc == 1 && !isatty(STDIN_FILENO)) {
        return pipe_mode(&env, builtin_commands);
    }
    (void)argv;
    if (argc > 1) {
        args_mode(argc, argv, &env, builtin_commands);
    }
    disable_raw_mode();
    return last_return;
}
