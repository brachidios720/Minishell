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
    if (tmp == NULL || tmp->str == NULL) {
        fprintf(stderr, "Erreur : pointeur nul détecté dans ft_check_builtins\n");
    }
    if(ft_strncmp(tmp->str, "env", ft_strlen("env")) == 0)
        ft_env(env);
    else if(ft_strncmp(tmp->str, "pwd", ft_strlen("pwd")) == 0)
        ft_pwd();
    else if(ft_strncmp(tmp->str, "echo", ft_strlen("echo")) == 0)
        ft_echo(tmp->matrice, data);
    else if(ft_strncmp(tmp->str, "cd", ft_strlen("cd")) == 0)
       ft_cd(env, tmp->matrice);
    else if(ft_strncmp(tmp->str, "export", ft_strlen("export")) == 0)
        ft_export(env, tmp->matrice);
    else if(ft_strncmp(tmp->str, "unset", ft_strlen("unset")) == 0)
        ft_unset(env, tmp->matrice);
    else 
        exec(data, cmd);
    free(data->matrice);
}
