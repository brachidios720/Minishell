/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:53:56 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/11 16:04:39 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    init_data(t_data *data)
{
    data->chain = NULL;
    data->old_pwd = NULL;
    data->path = NULL;
    data->pwd = getcwd(NULL, PATH_MAX);
}