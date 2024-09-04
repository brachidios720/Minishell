/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:44:34 by spagliar          #+#    #+#             */
/*   Updated: 2024/01/16 10:44:38 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newnode;

	newnode = malloc(sizeof(t_list));
	if (!newnode)
	{
		return (NULL);
	}
	newnode->content = content;
	newnode->next = NULL;
	return (newnode);
}
/*
int main(void)
{
	char *test = "bonjour";
	t_list  *pos;
	pos = ft_lstnew(test);
	printf("%s\n", (char *)pos->content); //we print the data of pos.
	free (pos);
}
16-*before ft we return a ptr to a structure of type t_list.
24-1content-> t_list 2content-> fction
26-next: end node ->null
28-new node
*/
