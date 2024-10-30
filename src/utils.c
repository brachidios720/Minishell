/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:58:25 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/17 17:48:25 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
gére les erreurs d’arguments ou de terminaison du programme.
*/
void	ft_exit(int i)
{
	if (i == 1)
		printf("args error\n");
	exit(0);
}

/*
 Parcourt s1 et s2 tant que les caractères sont identiques,
 retourne la différence entre les 2 caractères non identiques rencontrés.
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned int )s1[i] - (unsigned int)s2[i]);
}

/*Objectif : creer une copy du tab de chaine de caractere
Role de la fonction : retourne une copy de notre environement
dans le tableau d'origine*/

char	**ft_strdup_tab(char **env)
{
	char	**new_tab;
	int		i;
	int		len;

	len = 0;
	while (env[len])
		len++;
	new_tab = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_tab[i] = ft_strdup(env[i]);
		if (!new_tab[i])
		{
			free(new_tab);
			return (NULL);
		}
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

/*
Parcourt s2 et copie chaque caractère dans s1, ajoutant \0 à la fin
*/
char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0 ;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

/*
Copie caractère par caractère jusqu'à atteindre n caractères ou la fin de s1.
*/
char	*ft_strncpy(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] && i < n)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
/*
La variable i est utilisée pour parcourir chaque élément
de la liste et compter le nombre de nœuds.
*/

int	ft_llstsize(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}
