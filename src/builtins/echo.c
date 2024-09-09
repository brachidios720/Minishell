/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:06:53 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/09 19:26:50 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_echo(char **argv)
{
	int		i;
	bool	new_line;

	i = 1;
	new_line = true;
	if (argv[1] && strcmp(argv[1], "-n") == 0)
	{
		new_line = false;
		i++;
	}
	while (argv[i])
	{
		write (1, argv[i], strlen(argv[i]));
		if (argv[i + 1])
		{
			write(1, " ", 1);
		}
		i++;
	}
	if (new_line)
	{
		write(1, "\n", 1);
	}
}
