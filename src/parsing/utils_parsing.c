#include "../../include/minishell.h"


int ft_check_pipe(char c)
{
    if(c == '|')
        return(1);
    return(0);
} 

int count_pipe(char *str)
{
    int i = 0;
    int y = 0;
    while(str[i])
    {
        if(str[i] == '|')
            y++;
        i++;
    }
    return(y);
}



// char **ft_cut_cont(char *str)
// {
//     int i = 0;
//     int y = 0;
//     while(str[i])
//     {
//         if(ft_check_pipe(str[i]) == 1)
//         {
//             char *dest = malloc((i + 1) * sizeof(char *));
//             dest = ft_strncpy(str, dest, i);
//             y = i;
//             return(dest);
//         }
//         i++;
//     }
//     return(NULL);
// }
