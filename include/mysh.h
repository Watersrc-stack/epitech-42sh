/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** sh header file
*/

#pragma once

#include "../src/history/include/hist_struct.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <termios.h>
#include "../src/alias/myalias.h"
#include "../src/shell_variables/shell_variables.h"
#include "../src/inhibitors/inhibitors.h"
#include "../src/line_edition/line_edition.h"
//#include "../src/backticks/backticks.h"


#define MAX_ARGS 1000
#define FDMAX 1020

char **string_to_array(char *str);
char *my_getenv(char *name, char **env);
void print_path(void);

int cd_command(char **args, char ***env);
int setenv_command(char **args, char ***env);
int unsetenv_command(char **args, char ***env);
int env_command(char **args, char ***env);

typedef struct built_commands_s {
    char *name;
    int (*func)(char **args, char ***env);
} built_commands_t;

typedef struct command_tree_node_s {
    struct command_tree_node_s *parent;
    char *value;
    struct command_tree_node_s *left;
    struct command_tree_node_s *right;
} command_tree_node_t;

#include "../src/tools/freedom.h"

void add_node(command_tree_node_t *current, char *value);
command_tree_node_t *init_tree(void);

int parse_command(char *line, char ***env, built_commands_t *built_commands);
int execute_tree(command_tree_node_t *root,
    char ***env, built_commands_t *built_commands, int fd_in);
int search_redirection(char *command, command_tree_node_t *root);
int exec_command(char *command, char ***env, built_commands_t *built_commands);
char **separate_command(char *line);

void print_tree(command_tree_node_t *root, int depth, char *side);

int free_array(char **array, int return_code);
int my_arraylen(char **array);
void nullize_string(char *str);
char *trim_space(char *str);
int is_space(char c);
char **my_to_word_array(char *line, char *separator);

void shrink_str(char *str);

int exec_bin(char **args, char **env, bool system);
int built_commands_wrapper(built_commands_t *built_commands,
    int i, char **args, char ***env);
int execute_alias(char **args, char ***env, built_commands_t *built_commands);
char **get_arg_script(char *str);
