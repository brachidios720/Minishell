/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarico <almarico@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:35:56 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/11/11 14:04:56 by almarico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//execute une commande integree "builtin" dans un processus enfant
void	exec_builtin(t_cmd *cmd, t_env **env, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0) // Processus enfant
	{
        // Exécute le builtin dans l'enfant
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
          // Quitter après l'exécution du builtin
	}
	else if (pid > 0)  // Processus parent
		waitpid(pid, NULL, 0);  // Attendre que le processus enfant se termine
	else
	{
		perror("Erreur de fork");
		exit(EXIT_FAILURE);
	}
}
//execute une commande externe via execve
void	exec_external(t_cmd *cmd, t_env **env)
{
     // Convertir env en tableau par execve
	char	*cmd_path;
	char	**envp;

	envp = env_list_to_array(env);
	cmd_path = find_command_path(cmd->matrice[0]);  // Trouver le chemin complet de la commande
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
	if (is_builtin(tmp->str) == 1)  // Si c'est un builtin
		exec_builtin(tmp, env, data);  // Terminer l'enfant après avoir exécuté le builtin
	else
		exec_external(tmp, env);  // Exécuter une commande externe via execve
}

//traiter une commande (pipe ou non)
void	process_commands(t_data *data, t_env **env, t_cmd **cmd)
{
    // Détection des redirections et heredocs pour la commande actuelle
	// detect_input_redirection(*cmd, data);
	// 	printf("je suis ds process commands input\n");
	// detect_output_redirection(*cmd, data);
	// 	printf("je suis ds process commands output\n");
	detect_redirection(*cmd, data);
	handle_redirection(*cmd, data);
	if (count_pipe(data->line))
	{
		// Appeler la fonction qui gère l'exécution des commandes pipées
		exec_pipe_chain(data, cmd, env);
	}
	else
		exec_cmd(data, cmd, env);// Si pas de pipe, exécuter la commande (builtin ou externe)
}
