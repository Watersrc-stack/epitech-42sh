/*
** EPITECH PROJECT, 2024
** kehnsh
** File description:
** print_history.c
*/

#include "../../../include/mysh.h"

static void print_index_hist(int indx)
{
    printf("  %d\t", indx);
}

static void print_hours_hist(int hours, int minute)
{
    printf("%d:%d\t", hours, minute);
}

static void print_command_hist(char *cmd)
{
    printf("%s\n", cmd);
}

void print_all_history(void)
{
    history_t *tmp = hist()->history;

    while (tmp != NULL) {
        print_index_hist(tmp->command_index);
        print_hours_hist(tmp->hours, tmp->minutes);
        print_command_hist(tmp->cmd);
        tmp = tmp->next;
    }
}

static int count_node(history_t *list)
{
    history_t *tmp = list;
    int nb = 0;

    while (tmp != NULL) {
        nb++;
        tmp = tmp->next;
    }
    return nb;
}

void print_history(int num)
{
    int turn = 0;
    int nb = count_node(hist()->history);
    history_t *tmp = hist()->history;

    if (num == 0)
        num++;
    while (tmp != NULL) {
        if (turn < (nb - num))
            turn++;
        else {
            print_index_hist(tmp->command_index);
            print_hours_hist(tmp->hours, tmp->minutes);
            print_command_hist(tmp->cmd);
        }
        tmp = tmp->next;
    }
}
