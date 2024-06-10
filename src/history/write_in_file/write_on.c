/*
** EPITECH PROJECT, 2024
** kehnsh
** File description:
** get_info.c
*/

#include "../../../include/mysh.h"

int nbr_len(int number)
{
    int count = 0;

    if (number == 0)
        return 1;
    while (number != 0) {
        number /= 10;
        count++;
    }
    return count;
}

static void write_int(int fd, int num)
{
    char *buffer = malloc(sizeof(char) * (nbr_len(num) + 1));

    snprintf(buffer, (nbr_len(num) + 1), "%d", num);
    write(fd, buffer, strlen(buffer));
    free(buffer);
}

static void write_space(int fd, char *string)
{
    write(fd, string, strlen(string));
}

void add_history(char *line)
{
    time_t now;
    struct tm *tm;
    int h = 0;
    int m = 0;
    int ind = 0;

    time(&now);
    tm = localtime(&now);
    h = tm->tm_hour;
    m = tm->tm_min;
    ind = last_i(hist()->rev);
    hist_back(hist_node(ind, h, m, line), &hist()->history);
    hist_front(hist_node(ind, h, m, line), &hist()->rev);
}

void write_struct_hist(history_t *hist, int fd)
{
    history_t *tmp = hist;
    history_t *before = NULL;

    while (tmp != NULL) {
        write_int(fd, tmp->command_index);
        write_space(fd, " ");
        write_int(fd, tmp->hours);
        write_space(fd, ":");
        write_int(fd, tmp->minutes);
        write_space(fd, " ");
        write_space(fd, tmp->cmd);
        write_space(fd, "\n");
        free(tmp->cmd);
        before = tmp;
        tmp = tmp->next;
        free(before);
    }
}
