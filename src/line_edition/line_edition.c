/*
** EPITECH PROJECT, 2023
** B-PSU-200-MPL-2-1-42sh-killian.cassard
** File description:
** line_edition.c
*/

#include "../../include/mysh.h"
#include "line_edition.h"

struct termios orig_termios;

func_t array[] = {
    {CTRL_A, move_cursor_top_left},
    {CTRL_E, move_cursor_top_right},
    {CTRL_H, use_key_backspace},
    {CTRL_D, use_key_suppr},
    {CTRL_K, remove_right},
    {CTRL_U, remove_left},
    {CTRL_Y, paste},
    {CTRL_W, copy},
    {CTRL_L, clear_screen},
    {CTRL_P, up_in_history},
    {CTRL_N, down_in_history},
    {CTRL_T, reverse_two_chars},
    {CTRL_F, move_cursor_right},
    {CTRL_B, move_cursor_left},
    {BACKSPACE, use_key_backspace},
    {ENTER, insert_backslash_n},
    {TAB, autocompletion},
    {0, NULL}
};

line_t *line_struct(void)
{
    static line_t body = {
        .cursor_pos = 0,
        .text_length = 0,
        .line = NULL,
        .id = 0,
        .save = NULL
    };

    body = body;
    return &body;
}

void disable_raw_mode(void)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH | TCSANOW, &orig_termios);
}

void enable_raw_mode(void)
{
    struct termios raw;
    struct termios orig_termios;

    tcgetattr(STDIN_FILENO, &orig_termios);
    raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH | TCSANOW, &raw);
}

static int check_ctrl_command(char c)
{
    for (int i = 0; array[i].ptr != NULL; i++) {
        if (c == array[i].n) {
            array[i].ptr();
            return 0;
        }
    }
    return 1;
}

static int check_other_key(char c)
{
    if (check_ctrl_command(c) == 0) {
        return 0;
    } else if (c >= 32 && c <= 126) {
        insert_char(c);
        return 0;
    }
    return 1;
}

char *line_edition(void)
{
    char c;

    if (hist()->rev == NULL)
        line_struct()->id = 0;
    else
        line_struct()->id = hist()->rev->command_index;
    while (c != '\n') {
        if (read(STDIN_FILENO, &c, 1) == -1)
            exit(EXIT_FAILURE);
        if (c == '\033' && check_key() == 0)
            continue;
        check_other_key(c);
    }
    line_struct()->text_length = 0;
    line_struct()->cursor_pos = 0;
    return line_struct()->line;
}
