#include "../../include/minishell.h"

int     ft_check_option(t_data *data)
{
    int i = 0;
    int j = 0;
    while(data->cut_matrice[i])
    {
        if(ft_check_dash(data->cut_matrice[i]) == 1)
            return(1);
        j = ft_check_one_quote(data->cut_matrice[i]);
        if(j % 2 == 1)
        {
            printf(RED"error quote"RESET);
            return(1);
        }
        if(ft_check_pipe(data->line) == 1)
            return(1);
        i++;
    }
    return(0);
}

int     ft_check_dash(char *str)
{
    int i = 0;
    while(str[i])
    {
        if(str[i] == '-' && str[i + 1] == '-')
            return(1);
        i++;
    }
    return(0);
}
    