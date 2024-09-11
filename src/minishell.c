/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:54:54 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/11 16:11:26 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int ac, char **av, char **envp)
{
    t_data *data = NULL;
    
    (void)ac;
    print_minishell();
    init_data(data);
    ft_check_line(av, envp);
}
 
