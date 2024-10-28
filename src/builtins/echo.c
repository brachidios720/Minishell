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
//gestion de l option -n
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
//conversion pour $
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

//gestion $?
char *expand_variable(char *arg, t_data *data)
{
    char *result = malloc(1100); // taille pour resultat
    int i = 0;
    int j = 0;
    
    while (arg[i])
    {
        if (arg[i] == '$' && arg[i + 1] == '?')
        {
            // Insére la valeur de data->last_exit_status à la place de "$?"
            char *status_str = ft_itoa_m(data->last_exit_status);
            strcpy(&result[j], status_str);
            j += strlen(status_str);
            i += 2; // avance de deux caractères pour sauter "$?"
        }
        else
        {
            result[j++] = arg[i++];
        }
    }
    result[j] = '\0';
    return result;
}

void	ft_echo(char **argv, t_data *data)
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
		{ 
            ft_putstr_fd(output, 1);
			//ft_putstr_fd("\n", 1);
		}
		else
			ft_putstr_fd("", 1);
        if (argv[i + 1])
			// Affiche un espace entre les arguments
            ft_putstr_fd(" ", 1);
        i++;
	}
	// Affiche un espace si l option -n est activee
	//if (new_line)
	//	ft_putstr_fd(" ",1);
	// Affiche un saut de ligne si l'option -n n'est pas activée
    if (new_line)
       ft_putstr_fd("\n",1);
}
//echo sans options -> ajoute un saut de ligne par defaut
//echo -n -> supprime le saut de ligne
//echo -nnnnn -> marche comme -n
 
