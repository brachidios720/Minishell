/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 09:48:45 by spagliar          #+#    #+#             */
/*   Updated: 2023/05/06 09:48:46 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		c;
	char	*a;

	i = 0;
	c = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	i = ft_strlen(s);
	a = malloc(sizeof(char) * (i + 1));
	if (a == NULL)
		return (NULL);
	while (s[c])
	{
		a[c] = f(c, s[c]);
		c++;
	}
	a[c] = '\0';
	return (a);
}
