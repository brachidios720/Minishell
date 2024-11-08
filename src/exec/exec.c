/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <spagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:53:41 by spagliar          #+#    #+#             */
/*   Updated: 2024/11/08 18:50:02 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void exec_cmd(t_data *data, t_cmd **cmd, t_env **env)
{
    pid_t pid;
    int status;
    int pidt[2];
    t_cmd *tmp;

    tmp = *cmd;
    pid = fork();
    if (pid == -1) 
    {
        perror("Erreur de fork");
        return;
    }
    if (pid == 0)// Processus enfant
    {
        printf("zzzz\n");
        
        dup2(pidt[1], STDOUT_FILENO);
        close(pidt[0]);
        close(pidt[1]);
        // Exécuter le builtin ou la commande externe
        execute_command_or_builtin(&tmp, env, data);
        exit(EXIT_SUCCESS);
    } 
    else  // Processus parent
    {
        waitpid(pid, &status, 0);
        data->last_exit_status = WEXITSTATUS(status);
    }
}
