/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 10:27:45 by spagliar          #+#    #+#             */
/*   Updated: 2023/05/07 10:28:17 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*ft_zero(void)
{
	char	*ret;

	ret = malloc(sizeof(char) * 2);
	if (!ret)
		return (NULL);
	ret[0] = '0';
	ret[1] = '\0';
	return (ret);
}

static char	*ft_return(char buff[])
{
	char	*ret;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(buff);
	ret = malloc(sizeof(char) * len + 1);
	if (!ret)
		return (NULL);
	while (--len >= 0)
		ret[i++] = buff[len];
	ret[i] = '\0';
	return (ret);
}

char	*ft_itoa(int n)
{
	char	buff[12];
	long	nb;
	int		i;
	int		negatif;

	i = 0;
	nb = (long)n;
	negatif = 0;
	if (!nb)
		return (ft_zero());
	if (nb < 0)
	{
		negatif = 1;
		nb = -nb;
	}
	while (nb)
	{
		buff[i++] = (nb % 10) + 48;
		nb /= 10;
	}
	if (negatif)
		buff[i++] = '-';
	buff[i] = '\0';
	return (ft_return(buff));
}
