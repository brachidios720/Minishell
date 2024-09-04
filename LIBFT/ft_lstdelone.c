/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:05:46 by spagliar          #+#    #+#             */
/*   Updated: 2024/01/18 19:05:51 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
//#include <stdio.h>

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
	{
		return ;
	}
	if (lst)
	{
		(*del)(lst->content);
		free(lst);
	}
}

/*
int	main(void)
{
	t_list	*head;

	head = malloc(sizeof(t_list));
	if (!head)
	{
		return (0);
	}
	head->content = strdup("delete");
	printf("%p\n", head->content);
	ft_lstdelone(head, free);
	return (0);
}*/
