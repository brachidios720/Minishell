#include "../../include/minishell.h"

int count_pipe(char *str)
{
    int i;
    int y;
    
    i = 0;
    y = 0;
    while(str[i])
    {
        if(str[i] == '|')
            y++;
        i++;
    }
    return(y);
}

void    ft_cut_cont(char *str, t_data *data)
{
    int i = 0;
    data->pipe = count_pipe(str);
    if(count_pipe(str) >= 1)
        data->cut_matrice = ft_split(str, '|');
    else
    {
        data->cut_matrice = ft_split(str, '\0');
    }
    while(data->cut_matrice[i])
    {
        data->cut_matrice[i] = ft_strtrim(data->cut_matrice[i], " ");
        i++;
    }
}

int     ft_check_one_quote(char *str)
{
    int i = 0;
    int y = 0;
    while(str[i])
    {
        if(str[i] == '"')
            y++;
        i++;
    }
    return(y);
} 
