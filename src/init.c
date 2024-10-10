/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:53:56 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/17 17:23:11 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    init_data(t_data *data)
{
    //data->path = search_in_env(data, "PATH=");
    data->pwd = getcwd(NULL, PATH_MAX);
    data->old_pwd = data->pwd;
}
/*
char    *search_in_env(t_data *data, char *name)
{
    char *dest = NULL;
    int i = 0;
    while(data->copy_env[i])
    {
        if(ft_strcmp(data->copy_env[i], name) == 0)
        {
            dest = ft_strcpy(dest, data->copy_env[i]);
        }
        i++;
    }
    return(dest);
}*/

// char *ft_tab(char **av)
// {
//     int i = 0;
//     int len = 0;
//     while(av[i])
//     {
//         len += ft_strlen(av[i]);
//         i++;
//     }
//     char *dest = malloc((len + 1) * sizeof(char *));
//     if(!dest)
//         return(NULL);
//     i = 0;
//     int x = 0;
//     while(av[i])
//     {
//         int j = 0;
//         while(av[i][j])
//         {
//             dest[x] = av[i][j];
//             j++;
//             x++; 
//         }
//         i++;
//     }
//     dest[x] = '\0';
//     return(dest);
// }
