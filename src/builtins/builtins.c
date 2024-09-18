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

void	ft_check_bultins(char *line, char **env)
{
	char	**arg;

	if (line == NULL || line[0] == '\0')
		return ;
	arg = ft_split(line, ' ');
	if (ft_strcmp(arg[0], "env") == 0)
		ft_env(env);
	else if (ft_strcmp(arg[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(arg[0], "echo") == 0)
		ft_echo(arg);
	else if (ft_strcmp(arg[0], "unset") == 0)
		ft_unset(arg, env);
	else if (ft_strcmp(arg[0], "export") == 0)
		ft_export(arg, env);
	else
		write (1, "command not found\n", 19);
	free(arg);
}
