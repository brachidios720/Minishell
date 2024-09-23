/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:17:57 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/09 18:06:06 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void ft_check_line(char **av, char **env)
{
    signal(SIGINT, ft_handler);
    signal(SIGQUIT, ft_handlequit);

    char *line = readline("Minishell> ");

    if(line == NULL || ft_strcmp(line, "exit") == 0)
        return(free(line));
<<<<<<< Updated upstream
    ft_check_bultins(line, env);
    free(line);
    ft_check_line(av, env);
}
=======
    data->cut_matrice = ft_split(line, '|');
    data->pipe = count_pipe(line);
    int i = 0;
    int y = 0;
    while(data->cut_matrice[i])
    {
        printf("%s\n", data->cut_matrice[i]);
        y = ft_strlen(data->cut_matrice[i]);
        printf("%d\n", y);
        i++;
    }
    data->matrice = ft_split(line, ' '); // commance a matrice[0]
    init_data(data);
    ft_check_bultins(line, data);
    free(line);
    ft_check_line(av, env, data);
}
>>>>>>> Stashed changes
