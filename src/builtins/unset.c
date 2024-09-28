/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*      unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:50:03 by spagliar          #+#    #+#             */
/*   Updated: 2024/09/09 16:50:05 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/
void	check_env(char *var_to_delete, char **env)
{
	int	i;
	i = search_var(var_to_delete, env);
	if (i != -1)
	{
		free(env[i]);
		while (env[i] != NULL)
		{
			env[i] = env[i + 1];
			i++;
		}
	}
}

bool	delete_var(char *argv, char **env)
{
	int i;
	int j;

	i = 0;
	while (env[i] != NULL)
	{
		if (strncmp(env[i], argv, strlen(argv)) == 0 && env[i][strlen(argv)] == '=')
		{
			free(env[i]);
			j = i;
			while (env[j] != NULL)
			{
				env[j] = env[j + 1];
				j++;
			}
			return (true);
		}
		i++;
	}
	return (false);
}

int	ft_unset(char **argv, char **env)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (argv[i] != NULL)
	{
		if (!check_id(argv[i]))
			ret = 1;
		else if (search_var(argv[i], env) != -1)
			check_env(argv[i], env);
		else
			ret = 1;
		i++;
	}
	return (ret);
}
