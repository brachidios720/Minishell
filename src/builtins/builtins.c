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

void      ft_check_builtins(char *line, t_data *data, t_env **env, t_cmd **cmd)
{
    t_cmd *tmp;
    tmp = *cmd;
    if(line == NULL || line[0] == '\0')
        return;
    if(ft_strcmp(tmp->str, "env") == 0)
        ft_env(env);
    else if(ft_strcmp(tmp->str, "pwd") == 0)
        ft_pwd();
    else if(ft_strcmp(tmp->str, "echo") == 0)
        ft_echo(data->matrice);
    else if(ft_strcmp(tmp->str, "cd") == 0)
       ft_cd(env, line);
    else if(ft_strcmp(tmp->str, "export") == 0)
        ft_export(env, data->matrice);
    else if(ft_strcmp(tmp->str, "unset") == 0)
        ft_unset(env, data->matrice);
    else 
        exec(data, cmd);
    free(data->matrice);
}
