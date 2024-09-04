/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:14:08 by spagliar          #+#    #+#             */
/*   Updated: 2023/04/30 12:14:11 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	s;
	void	*a;

	s = nmemb * size;
	a = malloc(s);
	if (a == NULL)
		return (NULL);
	ft_bzero(a, s);
	return (a);
}
