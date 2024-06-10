/*
** EPITECH PROJECT, 2023
** B-PSU-200-MPL-2-1-42sh-killian.cassard
** File description:
** line_edition.h
*/

#pragma once

#include "../../include/mysh.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <termios.h>
#include <dirent.h>
#define CTRL_ 0
#define CTRL_H 8
#define CTRL_D 4
#define CTRL_K 11
#define CTRL_A 1
#define CTRL_Y 25
#define CTRL_W 23
#define CTRL_E 5
#define CTRL_L 12
#define CTRL_U 21
#define CTRL_P 16
#define CTRL_N 14
#define CTRL_T 20
#define CTRL_F 6
#define CTRL_B 2
#define BACKSPACE 127
#define ENTER 10
#define TAB 9

typedef struct func_s {
    int n;
    void (*ptr)(void);
} func_t;

typedef struct line_s {
    int cursor_pos;
    int text_length;
    char *line;
    int id;
    char *save;
} line_t;

line_t *line_struct(void);
void enable_raw_mode(void);
void disable_raw_mode(void);
void move_cursor_left(void);
void move_cursor_right(void);
void use_key_suppr(void);
void use_key_backspace(void);
int check_key(void);
void insert_char(char c);
char *line_edition(void);
void disable_raw_mode(void);
void enable_raw_mode(void);
void insert_backslash_n(void);
void empty_line(void);
void paste(void);
void copy(void);
void insert(char c);
void remove_right(void);
void clear_screen(void);
void reverse_two_chars(void);
void up_in_history(void);
void down_in_history(void);
void move_cursor_top_left(void);
void move_cursor_top_right(void);
void remove_left(void);
void autocompletion(void);
