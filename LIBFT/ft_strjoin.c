/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:29:20 by spagliar          #+#    #+#             */
/*   Updated: 2023/05/05 12:29:22 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)

{
	size_t	len1;
	size_t	len2;
	char	*strj;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	strj = malloc(len1 + len2 + 1);
	if (strj == NULL)
		return (NULL);
	ft_memcpy(strj, s1, len1);
	ft_memcpy(strj + len1, s2, len2 + 1);
	return (strj);
}
