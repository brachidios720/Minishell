/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:57:08 by spagliar          #+#    #+#             */
/*   Updated: 2023/05/05 13:57:09 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*a;

	i = 0;
	j = 0;
	if (!s1)
		return (NULL);
	while (ft_strchr(set, s1[i]) && i < ft_strlen(s1))
		i++;
	while (ft_strchr(set, s1[ft_strlen(s1) - j]) && i < ft_strlen(s1))
		j++;
	a = ft_substr(s1, i, (ft_strlen(&s1[i]) - j + 1));
	return (a);
}
