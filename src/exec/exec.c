/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pag <pag@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:53:41 by spagliar          #+#    #+#             */
/*   Updated: 2024/11/02 19:23:25 by pag              ###   ########.fr       */
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
    if (pipe(pidt) == -1)
    {
        perror("Erreur de création du pipe");
        return;
    }
    pid = fork();
    if (pid == -1) 
    {
        perror("Erreur de fork");
        return;
    }
    if (pid == 0)// Processus enfant
    {
        handle_redir_input(*cmd, data);
        handle_redir_output(*cmd);
        // Redirection pour le pipe si nécessaire
        dup2(pidt[1], STDOUT_FILENO);
        close(pidt[0]);
        close(pidt[1]);

        // Exécuter le builtin ou la commande externe
        execute_command_or_builtin(&tmp, env, data);
        exit(EXIT_SUCCESS);
    } 
    else  // Processus parent
    {
        //close(pidt[1]);
        waitpid(pid, &status, 0);
        data->last_exit_status = WEXITSTATUS(status);
        //dup2(pidt[0], STDIN_FILENO);
        //close(pidt[0]);
    }
}
