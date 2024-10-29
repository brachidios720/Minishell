/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  utils_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:53:41 by spagliar          #+#    #+#             */
/*   Updated: 2024/09/09 15:53:43 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**env_list_to_array(t_env **env_list)
{
    int     size = 0;
    t_env   *temp = *env_list;
    char    **env_array;
    int     i = 0;

    // Compter le nombre d'éléments dans la liste chaînée
    while (temp)
    {
        size++;
        temp = temp->next;
    }

    // Allouer de la mémoire pour le tableau de chaînes (taille +1 pour NULL final)
    env_array = malloc(sizeof(char *) * (size + 1));
    if (!env_array)
        return (NULL);

    // Remplir le tableau avec les variables d'environnement
    temp = *env_list;
    while (temp)
    {
        env_array[i] = ft_strdup(temp->content); // Copie chaque élément de la liste dans le tableau
        i++;
        temp = temp->next;
    }
    env_array[i] = NULL; // Terminer le tableau avec NULL

    return env_array;
}
/*
char	*ft_strchr_env(const char *s, int c)
{
	int			i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	if (!s[i])
		return (NULL);
	return ((char *)s);
}

int	ft_strncmp_env(const char *s1, const char *s2, size_t n)

{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
*/