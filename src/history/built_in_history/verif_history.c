/*
** EPITECH PROJECT, 2024
** kehnsh
** File description:
** verif_history.c
*/

#include "../../../include/mysh.h"

char *line_witout_st(char *string)
{
    char *line = malloc(sizeof(char) * strlen(string));
    int ind = 0;

    for (int i = 1; string[i] != '\0'; i++) {
        line[ind] = string[i];
        ind++;
    }
    line[ind] = '\0';
    return line;
}

void free_for_last_cmd(char *string, char *line)
{
    free(string);
    free(line);
}

void write_error_hist(char *line)
{
    if (line[0] == '\0') {
        write(2, "!", 1);
    } else
        write(2, line, strlen(line));
    write(2, ": Event not found.\n", 19);
}

static char *get_last_cmd_int(char *line)
{
    history_t *tmp = hist()->rev;
    char *cmd = NULL;
    int nb = 1;
    int del = atoi(line);

    while (tmp != NULL) {
        if (nb == del) {
            cmd = strdup(tmp->cmd);
            break;
        }
        nb++;
        tmp = tmp->next;
    }
    return cmd;
}

static char *find_last_cmd_int(char *string, char *line)
{
    char *cmd = NULL;

    cmd = get_last_cmd_int(line);
    if (cmd == NULL) {
        write_error_hist(line);
        return NULL;
    }
    free_for_last_cmd(string, line);
    string = strdup(cmd);
    free(cmd);
    return string;
}

static char *get_last_cmd(char *line)
{
    history_t *tmp = hist()->rev;
    char *cmd = NULL;

    while (tmp != NULL) {
        if (strncmp(line, tmp->cmd, strlen(line)) == 0) {
            cmd = strdup(tmp->cmd);
            break;
        }
        tmp = tmp->next;
    }
    return cmd;
}

char *find_last_cmd(char *string)
{
    char *line = line_witout_st(string);
    char *cmd = NULL;

    if (is_num(line) == 0 && strcmp("!", string) != 0)
        return find_last_cmd_int(string, line);
    if (strcmp("!", string) == 0) {
        write_error_hist(line);
        return NULL;
    }
    cmd = get_last_cmd(line);
    if (cmd == NULL) {
        write_error_hist(line);
        return NULL;
    }
    free_for_last_cmd(string, line);
    string = strdup(cmd);
    free(cmd);
    return string;
}

static int is_hist(char *line)
{
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '!')
            return 0;
    }
    return 1;
}

char *verif_hist(char *line)
{
    if (is_hist(line) == 0) {
        line = change_line(line);
        if (line != NULL)
            verif_hist(line);
    }
    return line;
}
