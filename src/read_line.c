/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:17:57 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/06 19:43:14 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void ft_check_line(char **env)
{
    char *line = readline("Minishell> ");

    if(line == NULL || ft_strcmp(line, "exit") == 0)
    {
        free(line);
        return;
    }
    if(ft_strcmp(line, "env"))
    {
        int i = 0;
        while(env[i] != NULL)
        {
            ft_printf("%s\n", env[i]);
            i++;
        }
    }
    free(line);
    ft_check_line(env);
}