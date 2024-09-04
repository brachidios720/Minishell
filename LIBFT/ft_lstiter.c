/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 10:06:17 by spagliar          #+#    #+#             */
/*   Updated: 2024/01/21 10:06:20 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	ft_lstiter(t_list *lst, void (*f)(void*))
{
	if (!f)
		return ;
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}

/*
void print_int(void *f)
{
	(void)f;
	printf("coucou\n");
}
int main(void)
{
	t_list *lst;
	lst = malloc(sizeof(t_list));
	if(!lst)
	{
		return(1);
	}
	int value;
	value = 1;
	lst->content = &value;
	lst->next = NULL;
	ft_lstiter(lst,&print_int);
	return(0);
}
*/