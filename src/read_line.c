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


void ft_check_line(char **av, char **envp, t_data *data, t_cmd **cmd, t_env **env)
{
    t_cmd *new_node = NULL;

    signal(SIGINT, ft_handler);
    signal(SIGQUIT, ft_handlequit);
    char *line = readline("Minishell> ");
    add_history(line);
    data->line = line;
    if(line == NULL || ft_strcmp(line, "exit") == 0)
        return(free(line));
    data->matrice = ft_split(line, ' '); // commance a matrice[0]
    init_data(data);
    ft_do_all(line, cmd, data, new_node);
    ft_check_bultins(line, data, env);
    ft_free(line, cmd);
    ft_check_line(av, envp, data, cmd, env);
}
