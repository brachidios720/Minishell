/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:08:16 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/09 18:09:22 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    ft_free_tab(char **av)
{
    int i = 0 ;
    while(av[i])
    {
        free(av[i]);
        i++;
    }
    free(av);
}

void ft_free_split(char **av)
{
    int i;

    i = 0;
    while(av[i])
    {
        free(av[i]);
        i++;
    }
    free(av);
}
