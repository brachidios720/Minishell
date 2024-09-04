/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:24:12 by spagliar          #+#    #+#             */
/*   Updated: 2023/05/02 09:24:14 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int				i;
	int				j;
	char			*stock;

	i = 0;
	j = ft_strlen(s);
	stock = (char *)malloc(sizeof(char) * (j + 1));
	if (!stock)
		return (NULL);
	while (i < j)
	{
		stock[i] = s[i];
		i++;
	}
	stock[i] = '\0';
	return (stock);
}
