/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** exec_command
*/

#include "../../include/mysh.h"
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/resource.h>

enum operators_e {
    PIPE = 1,
    DOUBLE_RIGHT = 2,
    RIGHT = 3,
    LEFT = 4,
    DOUBLE_LEFT = 5
};

struct exec_params_s {
    char ***env;
    built_commands_t *built_commands;
    int fd_in;
};

static int is_operator(char *str)
{
    if (strcmp(str, "|") == 0)
        return PIPE;
    if (strcmp(str, ">>") == 0)
        return DOUBLE_RIGHT;
    if (strcmp(str, ">") == 0)
        return RIGHT;
    if (strcmp(str, "<") == 0)
        return LEFT;
    if (strcmp(str, "<<") == 0)
        return DOUBLE_LEFT;
    return 0;
}

void free_node_tree(command_tree_node_t *root)
{
    if (root->left)
        free_node_tree(root->left);
    if (root->right)
        free_node_tree(root->right);
    free(root);
}

void execute_child_process(command_tree_node_t *root,
    int *fd, struct exec_params_s *params)
{
    close(fd[0]);
    if (root->right != NULL) {
        dup2(fd[1], 1);
    }
    execute_tree(root->left, params->env,
        params->built_commands, params->fd_in);
    exit(0);
}

void execute_parent_process(command_tree_node_t *root,
    int *fd, struct exec_params_s *params)
{
    close(fd[1]);
    if (root->right != NULL) {
        dup2(fd[0], 0);
        execute_tree(root->right, params->env, params->built_commands, fd[0]);
    }
}

int execute_pipe(command_tree_node_t *root, struct exec_params_s *params)
{
    int fd[2];
    pid_t pid;
    int saved_stdin = dup(0);
    static int pipe_counter = 0;

    if (pipe_counter >= FDMAX)
        return 1;
    pipe(fd);
    pid = fork();
    if (pid == 0) {
        execute_child_process(root, fd, params);
    } else {
        execute_parent_process(root, fd, params);
    }
    dup2(saved_stdin, 0);
    close(saved_stdin);
    pipe_counter = 0;
    return 0;
}

static void input_direction(command_tree_node_t *root,
    struct exec_params_s *params)
{
    int fd;
    int saved_stdin = dup(0);

    fd = open(root->right->value, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return;
    }
    dup2(fd, 0);
    execute_tree(root->left,
        params->env, params->built_commands, params->fd_in);
    close(fd);
    dup2(saved_stdin, 0);
    close(saved_stdin);
}

static void redirect_output(command_tree_node_t *root,
    struct exec_params_s *params)
{
    int fd;
    int saved_stdout = dup(1);

    fd = open(root->right->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("open");
        return;
    }
    dup2(fd, 1);
    execute_tree(root->left,
        params->env, params->built_commands, params->fd_in);
    close(fd);
    dup2(saved_stdout, 1);
    close(saved_stdout);
}

static void overwrite_output(command_tree_node_t *root,
    struct exec_params_s *params)
{
    int fd;
    int saved_stdout = dup(1);
    char *filename = strdup(root->right->value);

    shrink_str(filename);
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    free(filename);
    if (fd == -1) {
        perror("open");
        return;
    }
    dup2(fd, 1);
    execute_tree(root->left,
        params->env, params->built_commands, params->fd_in);
    close(fd);
    dup2(saved_stdout, 1);
    close(saved_stdout);
}

int execute_tree(command_tree_node_t *root,
    char ***env, built_commands_t *built_commands, int fd_in)
{
    struct exec_params_s params = {env, built_commands, fd_in};

    if (!is_operator(root->value))
        return exec_command(root->value, env, built_commands);
    if (is_operator(root->value) == LEFT)
        input_direction(root, &params);
    if (is_operator(root->value) == PIPE)
        if (execute_pipe(root, &params) == 1) {
            printf("mysh: pipe: Too many open files.\n");
            return 1;
        }
    if (is_operator(root->value) == RIGHT)
        overwrite_output(root, &params);
    if (is_operator(root->value) == DOUBLE_RIGHT)
        redirect_output(root, &params);
    return 0;
}
