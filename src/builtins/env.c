/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:35:54 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/09 16:45:58 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    ft_env(char **str)
{
    int i = 0;
    while(str[i] != NULL)
    {
        ft_printf("%s\n", str[i]);
        i++;
    }
}