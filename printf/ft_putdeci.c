/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdeci.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:18:20 by spagliar          #+#    #+#             */
/*   Updated: 2023/05/26 12:18:21 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

char	*ft_zero(void)

{
	char	*ret;

	ret = malloc(sizeof(char) * 2);
	if (!ret)
		return (NULL);
	ret[0] = '0';
	ret[1] = '\0';
	return (ret);
}

char	*ft_return(char buff[])
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

int	ft_putdeci(int nb)
{
	int			len;
	char		*stock;	

	len = 0;
	if (nb == 0)
		return (write (1, "0", 1));
	stock = ft_itoa(nb);
	len = ft_putstr(stock);
	free(stock);
	return (len);
}
//convertit l'entier en para -> en 1 chaîne de car renvoie la longueur
