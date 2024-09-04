/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:07:47 by spagliar          #+#    #+#             */
/*   Updated: 2023/04/18 15:08:08 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	lensrc;

	i = 0;
	lensrc = 0;
	while (src[lensrc] != '\0')
		lensrc++;
	if (size == 0)
		return (lensrc);
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (lensrc);
}
