/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:16:02 by spagliar          #+#    #+#             */
/*   Updated: 2024/09/04 18:39:18 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <stdint.h>
# include "../libft.h"

int		ft_conv(va_list arg, const char format);
int		ft_putchar(char c);
int		ft_printf(const char *format, ...);
int		ft_putstr(char *str);
int		ft_printhex(unsigned int nb);
int		ft_puthexa(unsigned int nb, const char format);
int		ft_lenhexa(unsigned int len);
int		ft_printunsign(unsigned int nb);
int		ft_putlen(unsigned int nb);
// int		ft_strlen(char *str);
char	*ft_return(char buff[]);
char	*ft_itoa(int n);
char	*ft_zero(void);
int		ft_putdeci(int nb);
void	ft_putchar_fd(char c, int fd);
int		ft_lenhex(uintptr_t	nb);
void	ft_ptrhex(uintptr_t nb);
void	ft_printptr(uintptr_t nb);
int		ft_pprintptr(unsigned long long nb);
int		ft_nblen(unsigned int nb);
int		ft_printnbru(unsigned int format);
char	*ft_itoau(unsigned int format, char *base);
char	*ft_pieceu(char *result, int index, unsigned int format, char *base);
int		ft_testu(unsigned int format, int index);

#endif
