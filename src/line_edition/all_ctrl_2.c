/*
** EPITECH PROJECT, 2023
** B-PSU-200-MPL-2-1-42sh-killian.cassard
** File description:
** all_ctrl_2.c
*/

#include "../../include/mysh.h"

void move_cursor_top_left(void)
{
    for (int i = line_struct()->cursor_pos; i > 0; i--) {
        write(STDOUT_FILENO, "\033[D", 3);
        line_struct()->cursor_pos--;
    }
}

void move_cursor_top_right(void)
{
    for (int i = line_struct()->cursor_pos; i < line_struct()->text_length;
    i++) {
        write(STDOUT_FILENO, "\033[C", 3);
        line_struct()->cursor_pos++;
    }
}

void remove_left(void)
{
    while (line_struct()->cursor_pos > 0) {
        use_key_backspace();
    }
}
