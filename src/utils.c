/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:58:25 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/03 16:59:45 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void ft_exit(int i)
{
    if(i == 1)
        printf("args error\n");
    exit(0);
}