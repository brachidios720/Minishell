#include "../../include/minishell.h"


void    ft_handler(int a)
{
    (void)a;

    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    printf("i\n");
}

void    ft_handlequit(int b)
{
    (void)b;
}