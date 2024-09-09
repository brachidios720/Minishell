/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:35:52 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/09 16:45:13 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int    ft_pwd(void)
{
    char line[PATH_MAX];

    if(getcwd(line, PATH_MAX))
    {
        printf("%s\n", line);
        return(0);
    }
    else
    {
        ft_printf("error");
        return(1);
    }
}