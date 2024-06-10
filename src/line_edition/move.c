/*
** EPITECH PROJECT, 2023
** B-PSU-200-MPL-2-1-42sh-killian.cassard
** File description:
** move.c
*/

#include "../../include/mysh.h"

void move_cursor_left(void)
{
    if (line_struct()->cursor_pos > 0) {
        write(STDOUT_FILENO, "\033[D", 3);
        line_struct()->cursor_pos--;
    }
}

void move_cursor_right(void)
{
    if (line_struct()->cursor_pos < line_struct()->text_length) {
        write(STDOUT_FILENO, "\033[C", 3);
        line_struct()->cursor_pos++;
    }
}
