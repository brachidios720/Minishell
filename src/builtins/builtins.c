/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pag <pag@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:35:56 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/11/11 16:02:47 by pag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//execute une commande integree "builtin" dans un processus enfant
void	exec_builtin(t_cmd *cmd, t_env **env, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0) //processus enfant
	{
		if (ft_strcmp(cmd->matrice[0], "cd") == 0)
			ft_cd(env, cmd->matrice);
		else if (ft_strcmp(cmd->matrice[0], "echo") == 0)
			ft_echo(cmd->matrice, data);
		else if (ft_strcmp(cmd->matrice[0], "env") == 0)
			ft_env(env);
		else if (ft_strcmp(cmd->matrice[0], "pwd") == 0)
			ft_pwd();
		else if (ft_strcmp(cmd->matrice[0], "export") == 0)
			ft_export(env, cmd->matrice);
		else if (ft_strcmp(cmd->matrice[0], "unset") == 0)
			ft_unset(env, cmd->matrice);
	}
	else if (pid > 0) //Processus parent
		waitpid(pid, NULL, 0); //Attendre que le processus enfant se termine
	else
	{
		perror("Erreur de fork");
		exit(EXIT_FAILURE);
	}
}

//execute une commande externe via execve
void	exec_external(t_cmd *cmd, t_env **env)
{
	char	*cmd_path;
	char	**envp;

	envp = env_list_to_array(env);
	cmd_path = find_command_path(cmd->matrice[0]); //Trouver le chemin complet de la commande
	if (cmd_path == NULL)
	{
		perror("Commande non trouvée");
		exit(EXIT_FAILURE);
	}
	execve(cmd_path, cmd->matrice, envp);
}

//decider si la commande est builtin ou externe
void	execute_command_or_builtin(t_cmd **cmd, t_env **env, t_data *data)
{
	t_cmd	*tmp;

	tmp = *cmd;
	if (is_builtin(tmp->str) == 1) //Si c'est un builtin
		exec_builtin(tmp, env, data);
	else
		exec_external(tmp, env); // exec commande ext. via execve
}

//traiter une commande (pipe ou non)
void	process_commands(t_data *data, t_env **env, t_cmd **cmd)
{
	// Détection des redirections et heredocs pour la commande actuelle
	detect_input_redirection(*cmd, data);
	ft_printf("je suis ds process commands input\n");
	detect_output_redirection(*cmd, data);
	ft_printf("je suis ds process commands output\n");
	if ((*cmd)->input_redir_type == HEREDOC)
	{
		// Vérification que le délimiteur est bien défini
		if (!(*cmd)->delimiter)
		{
			ft_printf("le délimiteur du heredoc n'est pas défini cf process command.\n");
			return ;
		}
		// Appel de ft_heredoc après confirmation du délimiteur
		if (ft_heredoc(*cmd, data) == -1)
		{
			ft_printf("Erreur lors de la configuration du heredoc cf process command\n");
			return;
		}
	}
	if (count_pipe(data->line))
		exec_pipe_chain(data, cmd, env);
	else
		exec_cmd(data, cmd, env);
}
