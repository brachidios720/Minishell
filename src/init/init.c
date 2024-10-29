/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pag <pag@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:53:56 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/10/29 15:27:54 by pag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    init_data(t_data *data)
{
    //data->path = search_in_env(data, "PATH=");
    data->pwd = getcwd(NULL, PATH_MAX);
    data->old_pwd = &data->pwd;
    data->mat = NULL;
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
