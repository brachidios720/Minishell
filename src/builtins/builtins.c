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

void      ft_check_bultins(char *line, char **env, t_data *data)
{
    if(line == NULL || line[0] == '\0')
        return;
    // char **arg = ft_split(line, ' ');
    if(ft_strcmp(data->matrice[0], "env") == 0)
        ft_env(env);
    else if(ft_strcmp(data->matrice[0], "pwd") == 0)
        ft_pwd();
    else if(ft_strcmp(data->matrice[0], "echo") == 0)
        ft_echo(data->matrice);
    else if(ft_strcmp(data->matrice[0], "cd") == 0)
        ft_cd(data);
    else 
        write(1, "command not found\n", 19);
    free(data->matrice);
}
