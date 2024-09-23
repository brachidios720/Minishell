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

int main(int ac, char **av, char **envp)
{
    t_data *data = NULL;
    (void)ac;
    print_minishell();
    data = malloc(sizeof(t_data));
    data->copy_env = ft_strdup_tab(envp);
    ft_check_line(av, envp, data);
}