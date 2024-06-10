/*
** EPITECH PROJECT, 2023
** B-PSU-200-MPL-2-1-42sh-killian.cassard
** File description:
** edit_line.c
*/

#include "../../include/mysh.h"
#include "line_edition.h"

void use_key_suppr(void)
{
    if (line_struct()->cursor_pos < line_struct()->text_length) {
        for (int i = line_struct()->cursor_pos;
        i < line_struct()->text_length - 1; i++) {
            line_struct()->line[i] = line_struct()->line[i + 1];
        }
        line_struct()->text_length--;
        write(STDOUT_FILENO, "\033[P", 3);
    }
}

void use_key_backspace(void)
{
    if (line_struct()->cursor_pos > 0) {
        for (int i = line_struct()->cursor_pos - 1;
        i < line_struct()->text_length - 1; i++) {
            line_struct()->line[i] = line_struct()->line[i + 1];
        }
        line_struct()->text_length--;
        line_struct()->cursor_pos--;
        write(STDOUT_FILENO, "\033[D", 3);
        for (int i = line_struct()->cursor_pos;
        i < line_struct()->text_length; i++) {
            write(STDOUT_FILENO, &line_struct()->line[i], 1);
        }
        write(STDOUT_FILENO, " ", 1);
        for (int i = line_struct()->cursor_pos;
        i < line_struct()->text_length + 1; i++) {
            write(STDOUT_FILENO, "\033[D", 3);
        }
    }
}

void insert_backslash_n(void)
{
    line_struct()->line = realloc(line_struct()->line,
    line_struct()->text_length + 2);
    line_struct()->line[line_struct()->text_length] = '\n';
    line_struct()->line[line_struct()->text_length + 1] = '\0';
    line_struct()->text_length++;
    line_struct()->cursor_pos++;
    write(STDOUT_FILENO, "\n", 1);
}

void insert(char c)
{
    line_struct()->line = realloc(line_struct()->line,
    line_struct()->text_length + 2);
    for (int i = line_struct()->text_length;
    i >= line_struct()->cursor_pos; i--) {
        line_struct()->line[i + 1] = line_struct()->line[i];
    }
    line_struct()->line[line_struct()->cursor_pos] = c;
    line_struct()->text_length++;
    line_struct()->cursor_pos++;
    write(STDOUT_FILENO, &c, 1);
    for (int i = line_struct()->cursor_pos;
    i < line_struct()->text_length; i++) {
        write(STDOUT_FILENO, &line_struct()->line[i], 1);
    }
    for (int i = line_struct()->cursor_pos;
    i < line_struct()->text_length; i++) {
        write(STDOUT_FILENO, "\033[D", 3);
    }
}

void insert_char(char c)
{
    if (line_struct()->line == NULL) {
        line_struct()->line = malloc(2);
        line_struct()->line[0] = c;
        line_struct()->line[1] = '\0';
        line_struct()->text_length++;
        line_struct()->cursor_pos++;
        write(STDOUT_FILENO, &c, 1);
    } else {
        insert(c);
    }
}
