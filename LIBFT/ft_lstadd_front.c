/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:02:05 by spagliar          #+#    #+#             */
/*   Updated: 2024/01/16 17:02:10 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
//#include <stdio.h>

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

/*
int	main(void)
{
	t_list	*head;
	t_list	*new_node;
	int		*content;
	t_list	*current;

	head = (NULL);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return (1);
	content = malloc(sizeof(int));
	if (content == NULL)
		return (1);
	*content = 5;
	new_node->content = content;
	new_node->next = NULL;
	ft_lstadd_front(&head, new_node);
	current = head;
	while (current != NULL)
	{
		printf("%p\n", current->content);
		current = current->next;
	}
	return (0);
}*/
