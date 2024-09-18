/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:53:41 by spagliar          #+#    #+#             */
/*   Updated: 2024/09/09 15:53:43 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	export_no_args(char **copy_env, int len)
{
	int	i;
	int	j;

	i = 0;
	if (!copy_env)
		return (false);
	sort_array(copy_env, len);
	while (i < len)
	{
		printf("declare -x");
		j = 0;
		while (copy_env[i][j] != '\0' && copy_env[i][j] != '=' )
		{
			printf ("%c", copy_env[i][j]);
			j++;
		}
		if (copy_env[i][j] != '\0' && copy_env[i][j] == '=')
		{
			printf ("=%s\"\n", &copy_env[i][j + 1]);
		}
		else
			printf ("\n");
		i++;
	}
	return (true);
}

int	exist(char *argv, char **copy_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (argv[i] && argv[i] != '=')
		i++;
	while (copy_env[j] != NULL)
	{
		if (!ft_strncmp(copy_env[j], argv, strlen(argv))
			&& (copy_env[j][i] == '\0' || copy_env[j][i] == '='))
			return (j);
		j++;
	}
	return (-1);
}

bool	export(char *argv, char **copy_env)
{
	int		len;
	int		pos;
	char	*value;
	char	**new_env;
	int		i;

	len = 0;
	pos = exist(argv, copy_env);
	value = ft_strdup(argv);
	if (!value)
		return (false);
	if (pos >= 0)
	{
		free((copy_env)[pos]);
		(copy_env)[pos] = value;
		return (true);
	}
	else
	{
		while ((copy_env)[len] != NULL)
			len++;
		new_env = malloc((len + 2) * sizeof(char *));
		if (!new_env)
		{
			free (value);
			return (false);
		}
		i = 0;
		while ((*copy_env)[i])
		{
			new_env[i] = (copy_env)[i];
			i++;
		}
		new_env[i] = value;
		new_env[i + 1] = NULL;
		free(*copy_env);
		copy_env = new_env;
	}
	return (true);
}

int	ft_export(char **argv, char **copy_env)
{
	int	exit;
	int	i;
	int	len;

	exit = 0;
	i = 1;
	len = 0;
	while ((copy_env)[len])
		len++;
	if (!argv || !argv[i])
	{
		if (copy_env && !export_no_args(copy_env, len))
			return (-1);
		return (0);
	}
	while (argv[i])
	{
		if (!check_id(argv[i]))
			exit = 1;
		else if (!export(argv[i], copy_env))
			return (-1);
		i++;
	}
	return (exit);
}
