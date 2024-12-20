/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pag <pag@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:35:56 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/11/13 20:31:46 by pag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void exec_builtin(t_cmd *cmd, t_env **env, t_data *data)
{
    // Les builtins qui doivent être exécutés dans le processus parent
    if (ft_strcmp(cmd->matrice[0], "export") == 0)
        ft_export(env, cmd->matrice);
    else if (ft_strcmp(cmd->matrice[0], "unset") == 0)
        ft_unset(env, cmd->matrice);
    else if (ft_strcmp(cmd->matrice[0], "cd") == 0)
        ft_cd(env, cmd->matrice);
    
    else
    {
        // Autres commandes peuvent être forkées
        pid_t pid = fork();
        
        if (pid == 0) // Processus enfant
        {
            // Exécute les autres builtins dans l'enfant
            // if (ft_strcmp(cmd->matrice[0], "cd") == 0)
            //     ft_cd(env, cmd->matrice);
            if (ft_strcmp(cmd->matrice[0], "echo") == 0)
                ft_echo(cmd->matrice, data, cmd->output_fd);
            else if (ft_strcmp(cmd->matrice[0], "env") == 0)
                ft_env(env);
            else if (ft_strcmp(cmd->matrice[0], "pwd") == 0)
                ft_pwd();
            exit(EXIT_SUCCESS);  // Quitter après l'exécution du builtin
        }
        else if (pid > 0)  // Processus parent
        {
            waitpid(pid, NULL, 0);  // Attendre que le processus enfant se termine
        }
        else
        {
            perror("Erreur de fork");
            exit(EXIT_FAILURE);
        }
    }
}

void exec_external(t_cmd *cmd, t_env **env)
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

void execute_command_or_builtin(t_cmd **cmd, t_env **env, t_data *data)
{
	t_cmd *tmp = *cmd;

    if (is_builtin(tmp->str))  // Si c'est un builtin
    {
        if (ft_strncmp(tmp->str, "export", ft_strlen("export")) == 0 || ft_strncmp(tmp->str, "unset", ft_strlen("unset")) == 0 || ft_strncmp(tmp->str, "cd", ft_strlen("cd")) == 0)
        {
            //printf("IIIII\n");
            exec_builtin(tmp, env, data);  // Exécute directement sans fork
        }
        else
        {
            pid_t pid = fork();
            if (pid == 0)
            {
                exec_builtin(tmp, env, data);
                exit(EXIT_SUCCESS);
            }
            else if (pid > 0)
            {
                waitpid(pid, NULL, 0);
            }
            else
            {
                perror("Erreur de fork");
                exit(EXIT_FAILURE);
            }
        }
    }
    else
    {
        exec_external(tmp, env);  // Exécuter une commande externe via execve
    }
}

void	process_commands(t_data *data, t_env **env, t_cmd **cmd)
{
	detect_redirection(*cmd, data);
	if ((*cmd)->redir_type[0] > 0)
	{
		trim_redirections(&data->line);
		ft_free_tab((*cmd)->matrice);
		(*cmd)->matrice = ft_splitt(data->line, ' ');
		trim_quotes((*cmd)->matrice);
	}
	handle_redirection(*cmd, data);
   // printf("after handle redir\n");
	exec_redir(cmd, data, env);
}
