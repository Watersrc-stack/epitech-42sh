/*
** EPITECH PROJECT, 2023
** B-PSU-200-MPL-2-1-42sh-killian.cassard
** File description:
** all_ctrl.c
*/

#include "../../include/mysh.h"

static void revstr(char *str)
{
    int i = 0;
    int j = strlen(str) - 1;
    char temp;

    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

void remove_right(void)
{
    while (line_struct()->cursor_pos < line_struct()->text_length) {
        use_key_suppr();
    }
}

void paste(void)
{
    if (line_struct()->save == NULL)
        return;
    for (int i = 0; i < (int)strlen(line_struct()->save); i++) {
        insert(line_struct()->save[i]);
    }
}

static void cpy_char(int *index, int *j)
{
    line_struct()->save[*j] = line_struct()->line[*index - 1];
    use_key_backspace();
    *j += 1;
    *index += 1;
}

void copy(void)
{
    int index = 0;
    int j = 0;

    if (line_struct()->line == NULL)
        return;
    line_struct()->save = malloc(sizeof(char) *
    line_struct()->text_length + 1);
    line_struct()->save = memset(line_struct()->save, 0,
    line_struct()->text_length + 1);
    index = line_struct()->cursor_pos;
    while (line_struct()->line[index - 1] == ' ') {
        cpy_char(&index, &j);
    }
    while (line_struct()->line[index - 1] != ' ' && index > 0) {
        cpy_char(&index, &j);
    }
    revstr(line_struct()->save);
}

void clear_screen(void)
{
    write(1, "\033[H\033[2J", 7);
    print_path();
    for (int i = 0; i < line_struct()->text_length; i++)
        write(STDOUT_FILENO, &line_struct()->line[i], 1);
}

void reverse_two_chars(void)
{
    char temp[2];

    if (line_struct()->cursor_pos < 1)
        return;
    temp[0] = line_struct()->line[line_struct()->cursor_pos - 2];
    temp[1] = line_struct()->line[line_struct()->cursor_pos - 1];
    use_key_backspace();
    use_key_backspace();
    insert(temp[1]);
    insert(temp[0]);
}
