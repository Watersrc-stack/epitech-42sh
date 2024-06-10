/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** mysh
*/

#include "../../../include/mysh.h"

char *my_strcat(char *dest, char *src)
{
    int j = 0;
    int dest_len = strlen(dest);
    int src_len = strlen(src);
    char *copy = malloc(sizeof(char) * (dest_len + src_len) + 1);

    for (int i = 0; i < dest_len; i++)
        copy[i] = dest[i];
    for (j = 0; j < src_len; j++)
        copy[dest_len + j] = src[j];
    copy[dest_len + j] = '\0';
    return copy;
}

int len_line(char *buff, int line)
{
    int nb = 0;
    int l = 0;

    for (int i = 0; buff[i] != '\0'; i++) {
        if (buff[i] == '\n')
            l++;
        if (l > line)
            break;
        if (l == line)
            nb++;
    }
    return nb;
}

static char *my_getline(char *buff, int l)
{
    int nb = 0;
    char *line = malloc(sizeof(char) * (len_line(buff, l) + 1));
    int ind = 0;

    for (int i = 0; buff[i] != '\0'; i++) {
        if (buff[i] == '\n')
            nb++;
        if (nb > l)
            break;
        if (nb == l) {
            line[ind] = buff[i];
            ind++;
        }
    }
    line[ind] = '\0';
    return line;
}

static int count_line(char *buff)
{
    int nb = 0;

    for (int i = 0; buff[i] != '\0'; i++)
        if (buff[i] == '\n')
            nb++;
    return nb;
}

static void free_val_bd(char *val, char *bd)
{
    free(val);
    free(bd);
}

static void parse_history(int fd, struct stat *st)
{
    char *buff = malloc(sizeof(char) * (st->st_size + 1));
    int ho = 0;
    int min = 0;
    char *val = NULL;
    int i = 0;
    char *bd = NULL;

    read(fd, buff, (st->st_size + 1));
    buff[st->st_size] = '\0';
    while (i < count_line(buff)) {
        bd = my_getline(buff, i);
        i++;
        ho = hist_i(bd, 1);
        min = hist_i(bd, 2);
        val = get_hist_value(bd, 3);
        hist_back(hist_node(hist_i(bd, 0), ho, min, val), &hist()->history);
        hist_front(hist_node(hist_i(bd, 0), ho, min, val), &hist()->rev);
        free_val_bd(val, bd);
    }
    free(buff);
}

char *get_home_in_env(char **env)
{
    int i = get_home_ind(env);
    char *buff = NULL;
    int ind = 0;

    if (i != -1)
        buff = malloc(sizeof(char) * (strlen(env[i]) + 1));
    else
        return NULL;
    for (int j = 5; env[i][j] != '\0'; j++) {
        buff[ind] = env[i][j];
        ind++;
    }
    buff[ind] = '\0';
    return buff;
}

void intilize_hist(char **env)
{
    char *home_path = get_home_in_env(env);
    char *home = NULL;
    char *path = verif_initilize(home, home_path);
    int fd = 0;
    struct stat st;

    if (path == NULL)
        return;
    fd = open(path, O_RDWR);
    if (fd < 0 || stat(path, &st) < 0) {
        return;
    } else {
        parse_history(fd, &st);
        close(fd);
        free(home);
        free(path);
    }
    free(home_path);
}

void save_history(char **env, int index, int tty)
{
    char *home_path = get_home_in_env(env);

    if (tty == 0)
        printf("exit\n");
    if (home_path == NULL) {
        exit(index);
    } else {
        save_history_next(home_path);
    }
    exit(index);
}
