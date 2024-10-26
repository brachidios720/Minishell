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

void	ft_pipe_first_cmd(t_data *data, t_cmd *cmd)
{
	pipe(data->pipe_fd); //creation pipe avec les descripteurs [0]lire et [1]ecrire
	if (cmd->input != STDIN_FILENO)
		data->read_fd_cmd = cmd->input;//chanmgement si redirection
	else
		data->read_fd_cmd = dup(STDIN_FILENO);//duplication si sortie standard
	if (cmd->output != STDOUT_FILENO)
	{
		close(data->pipe_fd[1]);
		data->pipe_fd[1] = cmd->output;
	}		               // Ferme l’extrémité de lecture du pipe
}

void	ft_pipe_last_cmd(t_data *data, t_cmd *cmd)
{
	close(data->read_fd_cmd);
	if (cmd->input != STDIN_FILENO)
	{
		close(data->pipe_fd[0]);
		data->read_fd_cmd = cmd->input;
	}
	else
		data->read_fd_cmd = cmd->input;
	close(data->pipe_fd[1]);
	if (cmd->output != STDOUT_FILENO)
		data->pipe_fd[1] = cmd->output;
	else
		data->pipe_fd[1] = dup(STDOUT_FILENO);
}

void	ft_pipe_middle_cmd(t_data *data, t_cmd *cmd)
{
	close(data->read_fd_cmd);
	if (cmd->input != STDIN_FILENO)
	{
		close(data->pipe_fd[0]);
		data->read_fd_cmd = cmd->input;
	}
	else
		data->read_fd_cmd = data->pipe_fd[0];
	close(data->pipe_fd[1]);
	pipe(data->pipe_fd);
	if (cmd->output != STDOUT_FILENO)
	{
		close(data->pipe_fd[1]);
		data->pipe_fd[1] = cmd->output;
	}
}

void	ft_pipe(t_data *data, t_cmd *cmd)
{
	if (data->flag == 1)              // Première commande
	{
		ft_pipe_first_cmd(data, cmd);
		data->flag = 0;
	}
	else if (cmd->next == NULL)        // Dernière commande
		ft_pipe_last_cmd(data, cmd);
	else                               // Commande intermédiaire
		ft_pipe_middle_cmd(data, cmd);
}

void	exec_pipe_chain(t_data *data, t_cmd *cmd)
{
	pid_t pid;

	while (cmd != NULL)
	{
		pipe(data->pipe_fd);           // Crée un pipe pour chaque commande

		pid = fork();
		if (pid == -1)
		{
			perror("Fork error");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)        // Processus enfant
		{
			handle_redir_in_out(cmd);
			ft_pipe(data, cmd);  // Configure les pipes en fonction de la position
			execve_cmd(data, cmd);        // Exécute la commande
			exit(EXIT_SUCCESS);
		}
		else                      // Processus parent
		{
			close(data->pipe_fd[1]);    // Ferme l’extrémité d’écriture pour le parent
			waitpid(pid, NULL, 0);// Attend la fin du processus enfant
		}
		cmd = cmd->next;
	}
}
