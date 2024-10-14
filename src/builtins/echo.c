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
char	*ft_itoa_m(int n)
{
	char	buff[12];
	long	nb;
	int		i;
	int		negatif;

	i = 0;
	nb = (long)n;
	negatif = 0;
	if (!nb)
		return (ft_zero());
	if (nb < 0)
	{
		negatif = 1;
		nb = -nb;
	}
	while (nb)
	{
		buff[i++] = (nb % 10) + 48;
		nb /= 10;
	}
	if (negatif)
		buff[i++] = '-';
	buff[i] = '\0';
	return (ft_return(buff));
}

char *expand_variable(char *arg, t_data *data)
{
    if (arg[0] == '$') 
	{
		printf("s\n");
        if (arg[1] == '?') 
            return (ft_itoa_m(data->last_exit_status)); 
		else 
            return (getenv(arg + 1));  // Cherche la variable d'environnement sans le '$'
    }
    return (arg);  // Retourner l'argument tel quel s'il ne s'agit pas d'une variable
}

void	ft_echo(char **argv, t_data *data)//cf parsing
{
	int		i;
	bool	new_line;
	char	*output;

	i = 1;
	new_line = true;

	while (argv[i] && echo_n(argv[i]))
	{
		new_line = false;
		i++;
	}
	while (argv[i])
	{
	 	output = expand_variable(argv[i], data);  // Vérifier l'expansion de variable
	    if (output) 
            write(1, output, strlen(output));
        if (argv[i + 1])
            write(1, " ", 1);
        i++;
	}
    if (new_line)
        write(1, "\n", 1);
}
//echo sans options -> ajoute un saut de ligne par defaut
//echo -n -> supprime le saut de ligne
//echo -nnnnn -> marche comme -n
