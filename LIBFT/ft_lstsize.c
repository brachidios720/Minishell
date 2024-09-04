/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:49:24 by spagliar          #+#    #+#             */
/*   Updated: 2024/01/18 15:49:27 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
/*
int	main(void)
{
	t_list	*lst;
	int		size;

	lst = malloc(sizeof(t_list));
	lst->content = strdup("first element");
	lst->next = NULL;
	size = ft_lstsize(lst);
	printf("new size =%d\n", size);
}
*/