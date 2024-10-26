/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:02:35 by spagliar          #+#    #+#             */
/*   Updated: 2024/10/16 15:02:37 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_pipe_first_cmd(int pipe_fd[2], t_cmd *cmd)
{
	pipe(pipe_fd); // Crée un pipe pour la première commande
	if (cmd->infile != STDIN_FILENO)
		dup2(cmd->infile, STDIN_FILENO);  // Redirige l'entrée standard si un fichier est spécifié
	dup2(pipe_fd[1], STDOUT_FILENO);      // Redirige la sortie vers le pipe
	close(pipe_fd[0]);                    // Ferme l’extrémité de lecture du pipe
}

void	ft_pipe_last_cmd(int pipe_fd[2], t_cmd *cmd)
{
	dup2(pipe_fd[0], STDIN_FILENO);       // Redirige l'entrée depuis le pipe
	if (cmd->outfile != STDOUT_FILENO)
		dup2(cmd->outfile, STDOUT_FILENO); // Redirige la sortie si un fichier de sortie est spécifié
	close(pipe_fd[1]);                    // Ferme l’extrémité d’écriture du pipe
}

void	ft_pipe_middle_cmd(int pipe_fd[2], t_cmd *cmd)
{
	(void)cmd;
	dup2(pipe_fd[0], STDIN_FILENO);       // Redirige l'entrée depuis le pipe précédent
	close(pipe_fd[1]);                    // Ferme l’extrémité d’écriture actuelle du pipe

	pipe(pipe_fd);                        // Crée un nouveau pipe pour cette commande
	dup2(pipe_fd[1], STDOUT_FILENO);      // Redirige la sortie vers le nouveau pipe
}

void	ft_pipe(t_data *data, t_cmd *cmd, int pipe_fd[2])
{
	if (data->flag == 1)              // Première commande
	{
		ft_pipe_first_cmd(pipe_fd, cmd);
		data->flag = 0;
	}
	else if (cmd->next == NULL)        // Dernière commande
		ft_pipe_last_cmd(pipe_fd, cmd);
	else                               // Commande intermédiaire
		ft_pipe_middle_cmd(pipe_fd, cmd);
}

void	exec_pipe_chain(t_data *data, t_cmd *cmd)
{
	pid_t pid;
	int pipe_fd[2] = {-1, -1};  // Pipe utilisé pour les redirections de chaque commande

	while (cmd != NULL)
	{
		pipe(pipe_fd);           // Crée un pipe pour chaque commande

		pid = fork();
		if (pid == -1)
		{
			perror("Fork error");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)        // Processus enfant
		{
			handle_redir_in_out(cmd);
			ft_pipe(data, cmd, pipe_fd);  // Configure les pipes en fonction de la position
			execve_cmd(data, cmd);        // Exécute la commande
			exit(EXIT_SUCCESS);
		}
		else                      // Processus parent
		{
			close(pipe_fd[1]);    // Ferme l’extrémité d’écriture pour le parent
			waitpid(pid, NULL, 0);// Attend la fin du processus enfant
		}
		cmd = cmd->next;
	}
}
