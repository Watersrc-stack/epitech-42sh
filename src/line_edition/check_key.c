/*
** EPITECH PROJECT, 2023
** B-PSU-200-MPL-2-1-42sh-killian.cassard
** File description:
** check_key.c
*/

#include "../../include/mysh.h"
#include "line_edition.h"

void up_in_history(void)
{
    char *new_line = NULL;

    if (line_struct()->id == 0)
        return;
    line_struct()->id--;
    new_line = get_hist_command_by_id(line_struct()->id);
    for (int i = 0; i < line_struct()->text_length; i++)
        move_cursor_right();
    for (int i = 0; i < line_struct()->text_length; i++)
        write(STDOUT_FILENO, "\033[D \033[D", 7);
    line_struct()->text_length = strlen(new_line);
    line_struct()->cursor_pos = line_struct()->text_length;
    line_struct()->line = strdup(new_line);
    for (int i = 0; i < line_struct()->text_length; i++)
        write(STDOUT_FILENO, &line_struct()->line[i], 1);
}

void empty_line(void)
{
    for (int i = 0; i < line_struct()->text_length; i++)
        move_cursor_right();
    for (int i = 0; i < line_struct()->text_length; i++)
        write(STDOUT_FILENO, "\033[D \033[D", 7);
    line_struct()->text_length = 0;
    line_struct()->cursor_pos = 0;
    line_struct()->line = strdup("");
}

void down_in_history(void)
{
    char *new_line = NULL;

    if (line_struct()->id == get_length_hist() - 1) {
        empty_line();
        return;
    }
    line_struct()->id++;
    new_line = get_hist_command_by_id(line_struct()->id);
    for (int i = 0; i < line_struct()->text_length; i++)
        move_cursor_right();
    for (int i = 0; i < line_struct()->text_length; i++)
        write(STDOUT_FILENO, "\033[D \033[D", 7);
    line_struct()->text_length = strlen(new_line);
    line_struct()->cursor_pos = line_struct()->text_length;
    line_struct()->line = strdup(new_line);
    for (int i = 0; i < line_struct()->text_length; i++)
        write(STDOUT_FILENO, &line_struct()->line[i], 1);
}

int find_key(char c)
{
    switch (c) {
    case 'A':
        up_in_history();
        return 0;
    case 'B':
        down_in_history();
        return 0;
    case 'C':
        move_cursor_right();
        return 0;
    case 'D':
        move_cursor_left();
        return 0;
    case '3':
        return 1;
    }
    return 0;
}

static int suppr_element(char *seq)
{
    if (seq[1] == '3') {
        read(STDIN_FILENO, &seq[2], 1);
        if (seq[2] == '~') {
            use_key_suppr();
            return 0;
        }
    }
    return 1;
}

int check_key(void)
{
    char seq[3];

    if (read(STDIN_FILENO, &seq[0], 1) != 1)
        return 0;
    if (read(STDIN_FILENO, &seq[1], 1) != 1)
        return 0;
    if (seq[0] == '[') {
        if (find_key(seq[1]) == 0)
            return 0;
        if (suppr_element(seq) == 0)
            return 0;
    }
    return 1;
}
