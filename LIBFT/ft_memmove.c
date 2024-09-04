/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:22:10 by spagliar          #+#    #+#             */
/*   Updated: 2023/04/18 11:23:47 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void*dest, const void*src, size_t n)
{
	size_t				i;
	unsigned char		*ndest;
	const unsigned char	*nsrc;

	i = 0;
	ndest = (unsigned char *) dest;
	nsrc = (const unsigned char *) src;
	if (ndest < nsrc)
	{
		while (i < n)
		{
			ndest[i] = nsrc[i];
			i++;
		}
	}
	else if (ndest > nsrc)
	{
		while (n > 0)
		{
			ndest [n - 1] = nsrc [n - 1];
			n--;
		}
	}
	return (dest);
}
