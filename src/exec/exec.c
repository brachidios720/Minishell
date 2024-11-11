/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pag <pag@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:53:41 by spagliar          #+#    #+#             */
/*   Updated: 2024/11/10 19:03:56 by pag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void exec_cmd(t_data *data, t_cmd **cmd, t_env **env)
{
    pid_t pid;
    int status;
    t_cmd *tmp;
    int fd_in;
	int fd_out;
	int i;

    tmp = *cmd;
	pid = fork();
	i = 0;
	if (pid < 0) 
    {
        perror("Erreur lors du fork");
        exit(EXIT_FAILURE);
    }
	// Processus enfant
    if (pid == 0) 
    {
		while(tmp->matrice[i])
		{
			printf("tmp :  %d %s\n", i, tmp->matrice[i]);
			i++;
		}
        // Gestion des redirections d'entrée
        fd_in = handle_redir_input(tmp, data);
		if (fd_in == -1)
		{
			perror("Erreur de redirection d'entrée");
            exit(EXIT_FAILURE);
		}
        if (fd_in != STDIN_FILENO)
        {
            if (dup2(fd_in, STDIN_FILENO) == -1)
            {
                perror("Erreur de redirection d'entrée");
                exit(EXIT_FAILURE);
            }
            close(fd_in);
        }
        // Gestion des redirections de sortie
        fd_out = handle_redir_output(tmp);
		if (fd_out == -1)
        {
            perror("Erreur de redirection de sortie");
            exit(EXIT_FAILURE);
        }
        if (fd_out != STDOUT_FILENO)
        {
            if (dup2(fd_out, STDOUT_FILENO) == -1)
            {
                perror("Erreur de redirection de sortie");
                exit(EXIT_FAILURE);
            }
            close(fd_out);
        }
        // Exécuter la commande ou le builtin
        execute_command_or_builtin(&tmp, env, data);
        exit(EXIT_SUCCESS);
    }
	// Processus parent
    else
    {
        waitpid(pid, &status, 0); // Attendre la fin du processus enfant
        data->last_exit_status = WEXITSTATUS(status);
    }
}





/*
void	exec_cmd(t_data *data, t_cmd **cmd, t_env **env)
{
	pid_t	pid;
	int		status;
	int		pidt[2];
	t_cmd	*tmp;
	int fd_in;
	int fd_out;

	tmp = *cmd;
	pid = fork();
	if (pid == -1)
	{
		perror("Erreur de fork");
		return ;
	}
	if (pid == 0)// Processus enfant
	{
		//printf("zzzz\n");
		dup2(pidt[1], STDOUT_FILENO);
		close(pidt[0]);
		close(pidt[1]);
        // Exécuter le builtin ou la commande externe
		if (pid == 0) // Processus enfant
		{
    		fd_in = handle_redir_input(tmp, data);
    		if (fd_in != STDIN_FILENO)
			{
        		if (dup2(fd_in, STDIN_FILENO) == -1)
				{
            		perror("Erreur de redirection d'entrée");
            		exit(EXIT_FAILURE);
        		}
        		close(fd_in);
    		}
    		// Si des redirections de sortie sont également nécessaires :
    		fd_out = handle_redir_output(tmp);
    		if (fd_out != STDOUT_FILENO)
			{
        		if (dup2(fd_out, STDOUT_FILENO) == -1)
				{
            		perror("Erreur de redirection de sortie");
            		exit(EXIT_FAILURE);
       			}
        		close(fd_out);
			}
    		execute_command_or_builtin(&tmp, env, data);
    		exit(EXIT_SUCCESS);
		}
		else  // Processus parent
		{
			waitpid(pid, &status, 0);
			data->last_exit_status = WEXITSTATUS(status);
		}
	}
}
*/
