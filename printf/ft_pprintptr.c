/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pprintptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:48:33 by spagliar          #+#    #+#             */
/*   Updated: 2023/05/27 17:48:36 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_lenhex(uintptr_t	nb)
{
	int	len;

	len = 0;
	while (nb)
	{
		len++;
		nb = nb / 16;
	}
	return (len);
}

void	ft_printptr(uintptr_t nb)
{
	if (nb >= 16)
	{
		ft_printptr(nb / 16);
		ft_printptr(nb % 16);
	}
	else
	{
		if (nb <= 9)
			ft_putchar_fd((nb + 48), 1);
		else
			ft_putchar_fd((nb - 10 + 'a'), 1);
	}
}

int	ft_pprintptr(unsigned long long nb)
{
	int	ptr;

	ptr = 0;
	if (nb == 0)
		return (write(1, "(nil)", 5));
	ptr += write(1, "0x", 2);
	ft_printptr(nb);
	ptr += ft_lenhex(nb);
	return (ptr);
}
