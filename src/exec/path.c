/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pag <pag@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:36:04 by spagliar          #+#    #+#             */
/*   Updated: 2024/11/11 15:43:20 by pag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
//cherche la valeur de path, ajoute "/"
char	*find_command_path(char *cmd)
{
	char	*path;
	char	**paths;
	char	*full_path;
	int		i;

	path = getenv("PATH");
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");//printf ("avec / : %s\n", full_path);
		full_path = ft_strjoin(full_path, cmd);//printf ("cmd : %s\n", full_path);
		if (access(full_path, X_OK) == 0)
		{
			//printf("valeur 1 :%s\n", full_path);
			return (full_path);
		}
		i++;
	}
	return (NULL);
}
