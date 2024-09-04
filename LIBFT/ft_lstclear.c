/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:07:57 by spagliar          #+#    #+#             */
/*   Updated: 2024/01/19 13:08:01 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!del || !lst || !*lst)
	{
		return ;
	}
	while (lst && *lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}

/*
int	main(void)
{
	t_list	*head;

	head = malloc(sizeof(t_list));
	if(!head)
	{
		return(1);
	}
	head->content = strdup("holaaaa");
	head->next = malloc(sizeof(t_list));
	head->next->content = strdup("que tal");
	printf("avant%p\n",head->content);
	printf("avant%p\n",head->next->content);
	ft_lstclear(&head->next, free);
	printf("apres: %p\n",head->content);
	printf("apres: %p\n",head->next->content);
	return (0);
}
*/
