/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:50:29 by spagliar          #+#    #+#             */
/*   Updated: 2023/05/24 15:50:30 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_lenhexa(unsigned int nb)
{
	int	len;

	len = 0;
	while (nb != 0)
	{
		len++;
		nb = nb / 16;
	}
	return (len);
}

void	ft_printnbr(unsigned int nb, const char format)
{
	if (nb >= 16)
	{
		ft_printnbr(nb / 16, format);
		ft_printnbr(nb % 16, format);
	}
	else
	{
		if (nb <= 9)
			ft_putchar(nb + 48);
		else
		{
			if (format == 'x')
				ft_putchar(nb -10 + 'a');
			else if (format == 'X')
				ft_putchar(nb -10 + 'A');
		}
	}
}

int	ft_puthexa(unsigned int nb, const char format)
{
	if (nb == 0)
		return (write (1, "0", 1));
	else
		ft_printnbr(nb, format);
	return (ft_lenhexa(nb));
}
