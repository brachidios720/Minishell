/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:54:54 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/17 15:25:27 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
    t_data *data = NULL;
    t_cmd *cmd = NULL;
    t_env *env = NULL;
    (void)ac;
    print_minishell();
    data = malloc(sizeof(t_data));
    env = init_env(envp);
    ft_check_line(av, envp, data, &cmd, &env);
    return (0);
}
