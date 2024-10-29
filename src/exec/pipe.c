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

//gere l exec de 2 commandes reliees par un pipe
void	handle_pipe(t_cmd *cmd1, t_cmd *cmd2)
{
	int		pipefd[2]; //2int = 2 extremites du pipe
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ;
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("error de fork pour cmd1");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execve_cmd(NULL, cmd1);
	}
	pid2 = fork();
	
	if (pid2 == -1)
	{
		perror("error de fork pour cmd2");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		execve_cmd(NULL, cmd2);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	exec_pipe_chain(t_data *data, t_cmd *cmd)
{
	printf("a\n");
	while (cmd != NULL && cmd->next != NULL)
	{
		printf("n\n");
		if (cmd->next && cmd->next->next)
		{
			printf("cmd->num : %d\n", cmd->num);
			handle_pipe(cmd, cmd->next->next);
			cmd = cmd->next->next;
		}
		else if(cmd->next)
		{
			printf("cmd->num2 : %d\n", cmd->num);
			exec_cmd(data, cmd);
			cmd = cmd->next;
		}
		else
		{
			exec_cmd(data, cmd);
			cmd = cmd->next;
		}
	}
}

