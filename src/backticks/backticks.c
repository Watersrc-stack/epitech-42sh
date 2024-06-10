/*
** EPITECH PROJECT, 2023
** B-PSU-200-MPL-2-1-42sh-killian.cassard
** File description:
** backticks.c
*/

#include "backticks.h"

global_backticks_t *backticks_struct(void)
{
    static global_backticks_t body = {
        .backticks = NULL
    };

    body = body;
    return &body;
}

static void redirect_cmd(char *cmd, char ***env, built_commands_t *build_cmd)
{
    int fd = open(".backticks", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int save_stdout = dup(1);

    if (fd == -1) {
        perror("open");
        return;
    }
    dup2(fd, 1);
    exec_command(cmd, env, build_cmd);
    dup2(save_stdout, 1);
    close(fd);
}

static char *read_file(char *file)
{
    int fd = open(file, O_RDONLY);
    char *result = malloc(sizeof(char) * 1024);
    int i = 0;

    if (fd == -1) {
        perror("open");
        return NULL;
    }
    while (read(fd, &result[i], 1) > 0)
        i++;
    result[i] = '\0';
    close(fd);
    return result;
}

char *find_result(char *cmd, int *i, char ***env, built_commands_t *build_cmd)
{
    int len = 0;
    char *backticks_command = NULL;
    int j = 0;

    *i += 1;
    while (cmd[*i + len] != '`')
        len++;
    backticks_command = malloc(sizeof(char) * (len + 1));
    while (cmd[*i] != '`') {
        backticks_command[j] = cmd[*i];
        j++;
        *i += 1;
    }
    backticks_command[j] = '\0';
    redirect_cmd(backticks_command, env, build_cmd);
    return read_file(".backticks");
}

static void free_backticks(void)
{
    backticks_t *tmp = backticks_struct()->backticks;
    backticks_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        if (tmp->result != NULL) {
            free(tmp->result);
            free(tmp);
        }
        tmp = next;
    }
    backticks_struct()->backticks = NULL;
}

static void complete_result(char **result, int *i, backticks_t *tmp)
{
    for (int k = 0; tmp->result[k + 1] != '\0'; k++) {
        (*result)[*i] = tmp->result[k];
        *i += 1;
    }
}

static char *make_new_command(char **command)
{
    backticks_t *tmp = backticks_struct()->backticks;
    char *result = malloc(sizeof(char) * 1024);
    int i = 0;

    for (int j = 0; (*command)[j] != '\0'; j++) {
        if ((*command)[j] == '`') {
            result[i] = '"';
            i++;
            complete_result(&result, &i, tmp);
            result[i] = '"';
            i++;
            j += strlen(tmp->result) + 1;
            tmp = tmp->next;
            break;
        }
        result[i] = (*command)[j];
        i++;
    }
    result[i] = '\0';
    return result;
}

static void pars_backticks(char *result)
{
    for (int i = 0; result[i] != '\0'; i++) {
        if (result[i] == '\n')
            result[i] = ' ';
    }
}

void add_backticks(char *cmd, int *i, char ***env, built_commands_t *built_cmd)
{
    backticks_t *new_backticks = malloc(sizeof(backticks_t));
    backticks_t *tmp = backticks_struct()->backticks;
    char *result = find_result(cmd, i, env, built_cmd);

    pars_backticks(result);
    new_backticks->result = result;
    new_backticks->next = NULL;
    if (tmp == NULL) {
        backticks_struct()->backticks = new_backticks;
        return;
    }
    tmp = backticks_struct()->backticks;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new_backticks;
}

void check_backticks(char **command, char ***env, built_commands_t *built_cmd)
{
    int i = 0;

    while ((*command)[i] != '\0') {
        if ((*command)[i] == '`')
            add_backticks(*command, &i, env, built_cmd);
        i++;
    }
    *command = make_new_command(command);
    free_backticks();
}
