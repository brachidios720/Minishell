/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <spagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:32:34 by spagliar          #+#    #+#             */
/*   Updated: 2024/11/06 20:45:04 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}*/

char	*ft_gnl_strjoin(char *carstock, char *buff)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	if (!buff)
		return (carstock);
	result = malloc(sizeof(char) * (ft_strlen(carstock) + ft_strlen(buff)) + 1);
	if (!result)
		return (NULL);
	while (carstock[i])
	{
		result[i] = carstock[i];
		i++;
	}
	while (buff[j])
		result[i++] = buff[j++];
	result[i] = '\0';
	return (result);
}

/*char	*ft_strchr(const char *s, int c)
{
	int			i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	if (!s[i])
		return (NULL);
	return ((char *)s);
}*/
