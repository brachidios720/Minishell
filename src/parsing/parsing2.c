#include "../../include/minishell.h"

int ft_check_pipe(char *str)
{
    int i = 0;
    while(str[i] == ' ' && str[i])
        i++;
    if(str[i] == '|')
    {
        printf(RED"error\n"RESET);
        return(1);
    }
    while(str[i])
        i++;
    if(str[i - 1] == '|')
    {
        printf(RED"error\n"RESET);
        return(1);
    }
    return(0);
}

