/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:41:46 by spagliar          #+#    #+#             */
/*   Updated: 2023/04/20 10:41:54 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[j] && j < size)
		j++;
	while (src[i] && size != '\0' && (i + j) < size - 1)
	{
		dst[i + j] = src[i];
		i++;
	}
	if (j < size)
		dst[i + j] = '\0';
	i = 0;
	while (src[i])
		i++;
	return (i + j);
}
