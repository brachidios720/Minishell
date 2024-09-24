/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  utils_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:53:41 by spagliar          #+#    #+#             */
/*   Updated: 2024/09/09 15:53:43 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//calcul la longueur (nbr d'elements) de la liste t_env
int	len_list(t_env *env)
{
	int		nb;//cptr pour le nbre d'elements
	t_env	*lst; //ptr parcourt la liste
	nb = 0;
	lst = env; //initialise au premier element d ela liste
	while (lst != NULL)
	{
		nb++;
		lst = lst->next;
	}
	return (nb);
}

//convertit la liste en un tab de chaine de car
char	**lst_to_arr(t_env *env)
{
	t_env	*lst; //ptr parcourt la liste
	char	**dest; //arr a retourner
	int		i;
	dest = malloc(sizeof(char *) * (len_list(env) + 1));
	if (!dest)
		return (NULL);
	lst = env;
	i = 0;
	while (lst) // Parcourir la liste chaînée jusqu'à la fin
	{
		dest[i] = strdup(lst->content);
		/*if (!dest[i])  // Vérification en cas d'échec de strdup
		{
			while (i > 0)
				free(dest[--i]);
			free(dest);
			return (NULL);
		}*/
		lst = lst->next;
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

// Trie le tableau de chaînes de caractères
void	sort_arr(char **arr, int len)
{
	int		i;
	int		j;
	int		diff;
	char	*tmp;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			diff = ft_strncmp(arr[i], arr[j], __INT_MAX__);
			if (diff > 0) //Si arr[i] > que arr[j] -> échange
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}


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
