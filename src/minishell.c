/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:54:54 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/09 17:10:07 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int main(int ac, char **av, char **envp)
{
    char **str;
    (void)ac;
    (void)av;
    //print_minishell();
    //ft_check_line(av, envp);
    str = ft_strdup_tab(envp);
    ft_env(str);
    
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
 
