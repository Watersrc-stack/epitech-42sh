/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** sh header file
*/

#pragma once

#include "fcntl.h"
#include "time.h"
#include <sys/stat.h>

typedef struct history_s {
    int command_index;
    int hours;
    int minutes;
    char *cmd;
    struct history_s *next;
} history_t;

typedef struct global_hist_s {
    history_t *history;
    history_t *rev;
    char *dup;
} global_hist_t;

void intilize_hist(char **env);
global_hist_t *hist(void);
history_t *hist_node(int num, int h, int m, char *val);
void hist_back(history_t *new, history_t **head);
void hist_front(history_t *new, history_t **head);
void save_history(char **env, int index, int tty);
void write_struct_hist(history_t *hist, int fd);
void add_history(char *line);
int last_i(history_t *history);
int history_command(char **args, char ***env);
void print_history(int num);
void print_all_history(void);
char *verif_hist(char *line);
char *my_strcat(char *dest, char *src);
char *change_line(char *line);
int get_ind_hist(char **tab);
char **caloc_array(int size);
char *find_last_cmd(char *string);
char **gen_tab_line(char *line);
int get_size_his(char *buff, int st);
int get_home_ind(char **env);
int hist_i(char *buff, int st);
char *get_hist_value(char *buff, int st);
int is_num(char *string);
char *re_assigne_line(char *dup, char *line);
char *get_hist_command_by_id(int id);
int get_length_hist(void);
char *verif_initilize(char *home, char *home_path);
void save_history_next(char *home_path);
