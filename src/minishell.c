/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:54:54 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/06 19:43:21 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int ac, char **av, char **envp)
{

    (void)ac;
    (void)av;
    ft_check_line(envp);
    // (void)av;
    // char *line = readline("Minishell> ");
    // char *buf = NULL;
    // if(ac < 2)
    //     ft_exit(1);
    // while(1)
    // {
    //     line = readline("Minishell> ");
    //     if(!line)
    //         break;
    //     buf = line;
    // }
    // while(1)
    // {
    //     readline("Minishell> ")
    // }
}
 
