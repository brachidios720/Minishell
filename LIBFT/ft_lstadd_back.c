/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:03:18 by spagliar          #+#    #+#             */
/*   Updated: 2024/01/18 18:03:23 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*endnode;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	endnode = *lst;
	while (endnode->next)
	{
		endnode = endnode->next;
	}
	endnode -> next = new;
}
	/*
	l21. add the new node to t_list
	l24. !=NULL 
	l25. Attribute endnode to next
	l27. browse the node to the end
	l29.attribute the newnode*/
