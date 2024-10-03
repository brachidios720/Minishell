/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:45:23 by spagliar          #+#    #+#             */
/*   Updated: 2024/09/09 14:45:25 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	echo_n(char *argv)
{
	int	i;

	if (argv[0] != '-' && argv[1] != 'n')
	{
		return (false);
	}
	i = 1;
	while (argv[i])
	{
		if (argv[i] != 'n')
		{
			return (false);
		}
		i++;
	}
	return (true);
}

void	ft_echo(char **argv)
{
	int		i;
	bool	new_line;

	i = 1;
	new_line = true;
	while (argv[i] && echo_n(argv[i]))
	{
		new_line = false;
		i++;
	}
	while (argv[i])
	{
		write (1, argv[i], strlen(argv[i]));
		if(argv[i] + 1)
		{
			write (1, " ", 1);
		}
		i++;
	}
	if (new_line)
	{
		write (1, "\n", 1);
	}
}
//echo sans options -> ajoute un saut de ligne par defaut
//echo -n -> supprime le saut de ligne
//echo -nnnnn -> marche comme -n
//echo --n -> cf parsing