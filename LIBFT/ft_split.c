/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 22:55:52 by spagliar          #+#    #+#             */
/*   Updated: 2023/05/12 22:55:54 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_verifchar(char c, char set)
{
	if (set == c)
		return (1);
	return (0);
}

char	*ft_strdupsize(const char *s, int size)
{
	int				i;
	char			*stock;

	i = 0;
	stock = (char *)malloc(sizeof(char) * (size + 1));
	if (!stock)
		return (NULL);
	while (i < size)
	{
		stock[i] = s[i];
		i++;
	}
	stock[i] = '\0';
	return (stock);
}

int	ft_nbredemot(char const*s, char c)
{
	int	i;
	int	nbrmot;

	i = 0;
	nbrmot = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			nbrmot++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (nbrmot);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	int		nbrmot;
	int		compteur;
	int		size;

	nbrmot = 0;
	compteur = 0;
	nbrmot = ft_nbredemot (s, c);
	new = malloc(sizeof (char *) * (nbrmot +1));
	if (!new)
		return (NULL);
	while (nbrmot > compteur)
	{
		size = 0;
		while (ft_verifchar (*s, c) == 1)
			s++;
		while (ft_verifchar (s[size], c) == 0 && s[size])
			size++;
		new[compteur] = ft_strdupsize (s, size);
		s = s + size;
		compteur++;
	}
	new[compteur] = NULL;
	return (new);
}
