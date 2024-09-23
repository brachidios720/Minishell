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

int len_list(t_env *env)
{
    int     len = 0;
    t_env   *current = env;

    while (current)
    {
        len++;
        current = current->next;
    }
    return (len);
}

char	**lst_to_arr(t_env *env)
{
	t_env	*lst;
	char	**dest;
	int		i;

	// Allouer de la mémoire pour le tableau de chaînes de caractères
	dest = (char **)malloc(sizeof(char *) * (len_list(env) + 1)); // +1 pour le NULL terminal
	if (!dest)
		return (NULL);
	
	lst = env;
	i = 0;
	while (lst)  // Parcourir la liste chaînée jusqu'à la fin
	{
		dest[i] = strdup((char *)lst->content);  // Copier le contenu de la liste (variable d'environnement)
		if (!dest[i])  // Vérification en cas d'échec de strdup
		{
			// En cas d'erreur de mémoire, libérer ce qui a été alloué
			while (i > 0)
				free(dest[--i]);
			free(dest);
			return (NULL);
		}
		lst = lst->next;  // Passer à l'élément suivant
		i++;
	}
	dest[i] = NULL;  // Terminer le tableau avec un pointeur NULL
	return (dest);
}

// Trie le tableau de chaînes de caractères
void	sort_array(char **arr, int len)
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
			// Comparaison lexicographique entre arr[i] et arr[j]
			diff = ft_strncmp(arr[i], arr[j], __INT_MAX__);  
			
			// Si arr[i] est plus grand que arr[j], on les échange
			if (diff > 0)
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
