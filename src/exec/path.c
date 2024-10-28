/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:36:04 by spagliar          #+#    #+#             */
/*   Updated: 2024/10/16 14:36:06 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//cherche la valeur de path, ajoute "/"
char	*find_command_path(t_data *data, t_cmd *cmd)
{
	int		i;

	data->path = getenv("PATH");
	data->paths = ft_split(data->path, ':');
	i = 0;
	while (data->paths[i])
	{
		data->full_path = ft_strjoin(data->full_path, "/");
		if (!data->full_path)
		{
			ft_free_split(data->paths);
			return (NULL);
		}
		data->full_path = ft_strjoin(data->full_path, cmd->str);
		if (access(data->full_path, X_OK) == 0)
			return (data->full_path);
		free(data->full_path);
		i++;
	}
	ft_free_split(data->paths);
	return (NULL);
}
