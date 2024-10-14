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
    data->cut_matrice = ft_split(str, '|');
    while(data->cut_matrice[i])
    {
        data->cut_matrice[i] = ft_strtrim(data->cut_matrice[i], " ");
        i++;
    }
}

