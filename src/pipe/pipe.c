/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarico <almarico@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:14:51 by spagliar          #+#    #+#             */
/*   Updated: 2024/11/14 10:15:09 by pag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//gére la redirection des descripteurs de fichiers. Elle configure la redirection
//d'un descripteur source (src_fd) vers un descripteur de destination (dest_fd)
// et effectue un nettoyage en fermant les descripteurs inutilisés.
void	handle_redir_fd(int src_fd, int dest_fd)
{
	dprintf(2, "src_fd: %d, dest_fd: %d\n", src_fd, dest_fd);
	if (src_fd != -1 && dup2(src_fd, dest_fd) == -1)
	{
		perror("Erreur redirection");
		exit(EXIT_FAILURE);
	}
	if (src_fd > 2)
	{
		close(src_fd);
		//perror("Erreur lors de la fermeture du descripteur");
	}	

}
void	exec_redir(t_cmd **cmd, t_data *data, t_env **env)
{
	pid_t pid;
	t_cmd	*tmp;
	tmp = *cmd;
	while (tmp != NULL)
	{
		pid = fork(); //debut processus child
		if (pid == -1)
		{
			perror("fork error\n");
			exit(EXIT_FAILURE);
		}
       // printf("pid = %d\n", pid);
		if (pid == 0)
		{
			handle_redirection(tmp, data);
             if (tmp->input_fd != -1)
                handle_redir_fd(tmp->input_fd, STDIN_FILENO);
            if (tmp->output_fd != -1)
                handle_redir_fd(tmp->output_fd, STDOUT_FILENO);
			//handle_redir_fd(tmp->input_fd, tmp->output_fd);
			execute_command_or_builtin(&tmp, env, data);
		}
		else //processus parent
		{
			waitpid(pid, NULL, 0); //attente fin de processus enfant	
		}
		tmp = tmp->next;
	}	
}

int	is_builtin_parent(const char *command) 
{
	return (ft_strcmp(command, "export") == 0 || ft_strcmp(command, "unset") == 0 || ft_strcmp(command, "cd") == 0);
}

void execute_builtin_in_parent(t_cmd *cmd, t_env **env)
{
	if (ft_strcmp(cmd->matrice[0], "export") == 0)
		ft_export(env, cmd->matrice);
	else if (ft_strcmp(cmd->matrice[0], "unset") == 0)
		ft_unset(env, cmd->matrice);
	else if (ft_strcmp(cmd->matrice[0], "cd") == 0)
		ft_cd(env, cmd->matrice);
}