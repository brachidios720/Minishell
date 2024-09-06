/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:58:25 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/06 19:43:36 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void ft_exit(int i)
{
    if(i == 1)
        printf("args error\n");
    exit(0);
}


int ft_strcmp(char *s1, char *s2)
{
    int i = 0;
    while(s1[i] && s1[i] == s2[i])
    {
        if(s1[i] != s2[i])
            return(0);
        i++;
    }
    return(1);
}