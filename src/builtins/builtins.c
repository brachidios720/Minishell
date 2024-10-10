/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:35:56 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/17 18:24:40 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void      ft_check_builtins(char *line, t_data *data, t_env **env)
{
    if(line == NULL || line[0] == '\0')
        return;
    if(ft_strcmp(data->matrice[0], "env") == 0)
        ft_env(env);
    else if(ft_strcmp(data->matrice[0], "pwd") == 0)
        ft_pwd();
    else if(ft_strcmp(data->matrice[0], "echo") == 0)
        ft_echo(data->matrice, data);
    //else if(ft_strcmp(data->matrice[0], "cd") == 0)
    //    ft_cd(data);
    else if(ft_strcmp(data->matrice[0], "export") == 0)
        ft_export(env, data->matrice);
    else if(ft_strcmp(data->matrice[0], "unset") == 0)
        ft_unset(env, data->matrice);
    else 
        write(1, "command not found\n", 19);
    free(data->matrice);
}
