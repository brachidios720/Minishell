/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:43:04 by spagliar          #+#    #+#             */
/*   Updated: 2023/04/26 13:43:14 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	llittle;

	i = 0;
	j = 0;
	llittle = ft_strlen(little);
	if (llittle == 0)
		return ((char *)big);
	while (big[i] != '\0' && len > i)
	{
		j = 0;
		while ((big[i + j] == little[j]) && (big[i] != '\0') && len > i + j)
		{
			j++;
			if (j == llittle)
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
	/* l14 : size_t len : longueur max de big recherchee pour little*/
	/* l16 pointeur sur la chaine big*/
	/* l17 compteur pour parcourir la chaine big*/
	/* l18 compteur de la sous chaine little*/
	/* l19 contient la longueur de la chaine de little*/

	/*big = eeedfabcedrfrgtedf;*/
	/*little = edf;*/
