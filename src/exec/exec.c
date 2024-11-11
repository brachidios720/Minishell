/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarico <almarico@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:53:41 by spagliar          #+#    #+#             */
/*   Updated: 2024/11/11 17:15:46 by almarico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//prepare le tableau argv en fonction des infos donnees dans cmd
// char **prepare_argv(t_cmd *cmd, char *cmd_path)
// {
// 	char **argv = malloc(sizeof(char *)*3); //3 elements
// 	if (!argv)
// 	{
// 		return (NULL);
// 	}
// 	argv[0] = cmd_path; //ls
// 	argv[1] = cmd->option; //-la
// 	argv[2] = NULL;

// 	return (argv);
// }

// //gestion de l envirionnement et execution + conversion
// void exec_with_env_and_redir(t_cmd *cmd, t_data *data)
// {
	
// 	char **envp;
// 	char *cmd_path = data->path;

// // Conversion de la liste des variables d'environnement en tableau
//     envp = env_list_to_array(&data->copy_env);
//     if (!envp)
//     {
//         perror("Erreur de conversion des variables d'environnement");
//         free(cmd_path);
//         return;
//     }
//     // Gérer les redirections (entrée/sortie)
//     handle_redir_in_out(cmd);
//     // Exécuter la commande avec execve
//     if (execve(cmd_path, cmd->matrice, envp) == -1)
//     {
//         perror("Erreur execve");
//         free(cmd_path);
//         free(envp);
//         exit(EXIT_FAILURE);
//     }
//     free(cmd_path);
//     free(envp);
// }

// void execve_cmd(t_data *data, t_cmd *cmd)
// {
//     // Trouver le chemin complet de la commande et le stocker dans `data->path`
//     data->path = find_command_path(cmd->matrice[0]);
//     if (!data->path)
//     {
//         printf("Commande non trouvée : %s\n", cmd->str);
//         return;
//     }

//     // Préparer les arguments pour execve et les stocker dans cmd->matrice
//     cmd->incmd = prepare_argv(cmd, data->path);
//     if (!cmd->incmd)
//     {
//         perror("Erreur de préparation des arguments");
//         free(data->path);
//         return;
//     }

//     // Gérer l'exécution et les redirections
//     exec_with_env_and_redir(cmd, data);
// }

// void exec_cmd(t_data *data, t_cmd **cmd, t_env **env)
// {
//     pid_t pid;
//     int status;
//     int pidt[2];
//     t_cmd *tmp;

//     tmp = *cmd;
//     pid = fork();
//     if (pid == -1) 
//     {
//         perror("Erreur de fork");
//         return;
//     }
//     if (pid == 0) 
// 	{
//        // printf("zzzz\n");
//         //handle_redir_in_out(&tmp);
//         dup2(pidt[1], STDOUT_FILENO);  // Rediriger la sortie de cmd1 vers le pipe
//         close(pidt[0]);
//         close(pidt[1]);
//         execute_command_or_builtin(&tmp, env); 
//         //perror("Erreur d'exécution de la commande");
//         exit(EXIT_SUCCESS);
//     } 
// 	else 
// 	{
//         waitpid(pid, &status, 0);
//         data->last_exit_status = WEXITSTATUS(status);
//     }
// }

void exec_cmd(t_data *data, t_cmd **cmd, t_env **env)
{
	pid_t	pid;
	int		status;
	t_cmd	*tmp;
	int		fd_in;
	int		fd_out;
	int		i;

	tmp = *cmd;
	pid = fork();
	i = 0;
	if (pid < 0)
	{
		perror("Erreur lors du fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		while (tmp->matrice[i])
		{
			printf("tmp :  %d %s\n", i, tmp->matrice[i]);
			i++;
		}
		fd_in = tmp->input_fd;
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
		fd_out = tmp->output_fd;
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
		execute_command_or_builtin(&tmp, env);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
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
