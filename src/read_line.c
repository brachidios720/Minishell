/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:17:57 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/18 14:19:31 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_check_line(char **av, char **env, t_data *data)
{
    signal(SIGINT, ft_handler);
    signal(SIGQUIT, ft_handlequit);

    char *line = readline("Minishell> ");
    add_history(line);
    data->line = line;
    if(line == NULL || ft_strcmp(line, "exit") == 0)
        return(free(line));
    data->cut_matrice = ft_split(line, '|');
    data->pipe = count_pipe(line);
    data->matrice = ft_split(line, ' '); // commance a matrice[0]
    init_data(data);
    ft_check_bultins(line, data);
    free(line);
    ft_check_line(av, env, data);
}