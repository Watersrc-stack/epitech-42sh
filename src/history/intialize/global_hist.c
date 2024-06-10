/*
** EPITECH PROJECT, 2024
** kehnsh
** File description:
** initialise_history.c
*/

#include "../../../include/mysh.h"

global_hist_t *hist(void)
{
    static global_hist_t body = {
            .history = NULL,
            .rev = NULL,
            .dup = NULL
    };

    body = body;
    return &body;
}
