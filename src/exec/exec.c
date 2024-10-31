/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pag <pag@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:53:41 by spagliar          #+#    #+#             */
/*   Updated: 2024/10/31 12:03:09 by pag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void exec_cmd(t_data *data, t_cmd **cmd, t_env **env)
{
    pid_t pid;
    int status;
    int pidt[2];
    t_cmd *tmp;
    int infile_fd;
    int outfile_fd;

    tmp = *cmd;
    pid = fork();
    if (pid == -1) 
    {
        perror("Erreur de fork");
        return;
    }
    if (pid == 0) //processus enfant
	{
        // Gestion des redirections d'entrée
        infile_fd = handle_redir_input(tmp, data);
        if (infile_fd == -1) {
            perror("Erreur dans la redirection d'entrée");
            exit(EXIT_FAILURE);
        }

        // Gestion des redirections de sortie
        outfile_fd = handle_redir_output(tmp);
        if (outfile_fd == -1) {
            perror("Erreur dans la redirection de sortie");
            exit(EXIT_FAILURE);
        }
        printf("zzzz\n");
        dup2(pidt[1], STDOUT_FILENO);  // Rediriger la sortie de cmd1 vers le pipe
        close(pidt[0]);
        close(pidt[1]);
        
        // Exécute la commande ou le builtin avec les redirections en place
        execute_command_or_builtin(&tmp, env, data); 
        exit(EXIT_SUCCESS);
    } 
	else //processus parent
	{
        //close(pidt[1]); // Ferme l'écriture du pipe dans le parent
        waitpid(pid, &status, 0);
        data->last_exit_status = WEXITSTATUS(status);
    }
}