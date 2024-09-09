/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:06:53 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/09 17:46:54 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	ft_echo(char **argv)
// {
// 	int		i;
// 	bool	new_line;

// 	i = 1;
// 	new_line = true;
// 	if (argv[1] && strcmp(argv[1], "-n") == 0)
// 	{
// 		new_line = false;
// 		i++;
// 	}
// 	while (argv[i])
// 	{
// 		write (1, argv[i], strlen(argv[i]));
// 		if (argv[i + 1])
// 		{
// 			write(1, " ", 1);
// 		}
// 		i++;
// 	}
// 	if (new_line)
// 	{
// 		write(1, "\n", 1);
// 	}
// 	return (0);
// }

void ft_echo(char **av)
{
    int i = 1;
    while (av[i])
    {
        write(1, av[i], ft_strlen(av[i]));
        if (av[i + 1])
            write(1, " ", 1);
        i++;
    }
    write(1, "\n", 1);
}

