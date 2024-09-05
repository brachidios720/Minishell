/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:40:54 by spagliar          #+#    #+#             */
/*   Updated: 2023/06/01 13:48:36 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_conv(va_list arg, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len = ft_putchar(va_arg(arg, int));
	else if (format == 's')
		len = ft_putstr(va_arg(arg, char *));
	else if (format == 'p')
		len = ft_pprintptr(va_arg(arg, uintptr_t));
	else if (format == '%')
		len = write (1, "%", 1);
	else if (format == 'x' || format == 'X')
		len = ft_puthexa(va_arg(arg, unsigned int), format);
	else if (format == 'i' || format == 'd')
		len = ft_putdeci(va_arg(arg, unsigned int));
	else if (format == 'u')
		len = ft_printnbru(va_arg(arg, unsigned int));
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list			arg;
	int				i;
	int				len;

	i = 0;
	len = 0;
	va_start(arg, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			len += ft_conv(arg, format[i + 1]);
			i++;
		}
		else
		{
			len += write(1, &format[i], 1);
		}
		i++;
	}
	va_end(arg);
	return (len);
}

/*int main(void)
{
	char	*i = "42";

	ft_printf("ecole %p\n%", i);
}*/
