/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pag <pag@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:08:16 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/11/13 16:43:10 by pag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    ft_free_tab(char **av)
{
    int i = 0 ;
    if (av == NULL)
	{
		return;
	}
    while(av[i])
    {
        free(av[i]);
        i++;
    }
    free(av);
}
//versiosns securisee pour eviter les doubles liberations
void ft_free(char *str, t_cmd **cmd)
{
	ft_lstclearr(cmd);
	if (str != NULL && str[0] != '\0')
	{
		free(str);
		str = NULL;
	}
	if (cmd != NULL && *cmd != NULL)
	{
		free (*cmd);
		*cmd = NULL;
	}
}
