/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:58:19 by spagliar          #+#    #+#             */
/*   Updated: 2023/04/16 14:58:24 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*ndest;
	const char	*nsrc;

	i = 0;
	ndest = (char *) dest;
	nsrc = (const char *)src;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		ndest[i] = nsrc[i];
		i++;
	}
	return (dest);
}
