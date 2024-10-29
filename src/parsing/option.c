#include "../../include/minishell.h"

int     ft_check_option(t_data *data)
{
    if(data->cut_matrice)
    {
        int i = 0;
        int j = 0;
        while(data->cut_matrice[i])
        {
            j = ft_check_one_quote(data->cut_matrice[i]);
            if(j % 2 == 1)
            {
                perror(RED"error quote"RESET);
                return(1);
            }
            if(ft_check_pipe(data->line) == 1)
            {
                printf(RED"error\n"RESET);
                return(1);
            }
            i++;
        }
    }
    return(0);
}

char    *ft_check_dash(char *str)
{
    int i = 0;
    int y = 0;
    int x = 0;
    char *find;
    while(str[i])
    {
        if((str[i] == '-' || str[i] == '/') && ft_isalpha(str[i + 1]))
        {
            y = i;
            i++;
            while(str[i] >= 'a' && str[i] <= 'z')
                i++;
            find = malloc(sizeof(char *) * ((i - y) + 1));
            while(y < i)
            {
                find[x] = str[y];
                y++;
                x++;
            }
            find[x] = '\0';
            return(find);
        }
        i++;
    }
    return(NULL);
}
    