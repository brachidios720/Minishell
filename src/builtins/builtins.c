/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:35:56 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/09 18:35:48 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void      ft_check_bultins(char *line, char **env)
{
    if(line == NULL || line[0] == '\0')
        return;
    char **arg = ft_split(line, ' ');
    if(ft_strcmp(arg[0], "env") == 0)
        ft_env(env);
    else if(ft_strcmp(arg[0], "pwd") == 0)
        ft_pwd();
    else if(ft_strcmp(arg[0], "echo") == 0)
        ft_echo(arg);
    else 
        write(1, "command not found\n", 19);
    free(arg);
}
