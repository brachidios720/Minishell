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

void    ft_env(t_env **env)
{
    t_env *ptr;

    ptr = *env;
    while(ptr)
    {
        ft_printf("%s\n", ptr->content);
        ptr = ptr->next;
    }
}
