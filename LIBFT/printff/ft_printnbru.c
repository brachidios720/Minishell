/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbru.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:31:56 by spagliar          #+#    #+#             */
/*   Updated: 2023/05/31 11:31:58 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_testu(unsigned int format, int index)
{
	if (format == 0)
		return (1);
	while (format != 0)
	{
		format = format / 10;
		index++;
	}
	return (index);
}

char	*ft_pieceu(char *result, int index, unsigned int format, char *base)
{
	while (index >= 0 && format > 0)
	{
		result[index--] = base[format % 10];
		format = format / 10;
	}
	return (result);
}

char	*ft_itoau(unsigned int format, char *base)
{
	int				index;
	char			*result;

	index = 0;
	index = ft_testu(format, index);
	result = malloc(sizeof(char) * index + 1);
	if (!result)
		return (NULL);
	if (format == 0)
		result[0] = '0';
	result[index] = '\0';
	if (index != 0)
		result = ft_pieceu(result, index - 1, format, base);
	return (result);
}

int	ft_printnbru(unsigned int format)
{
	int		len;
	char	*str;
	char	*base;

	base = "0123456789abcdef";
	str = ft_itoau(format, base);
	len = ft_putstr(str);
	free(str);
	return (len);
}
