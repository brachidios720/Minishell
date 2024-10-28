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
// void handle_pipe(t_cmd *cmd1, t_cmd *cmd2)
// {
//     int pipefd[2];
//     pid_t pid1, pid2;

//     // Création du pipe
//     if (pipe(pipefd) == -1) {
//         perror("Erreur de création du pipe");
//         exit(EXIT_FAILURE);
//     }
//     pid1 = fork();
//     if (pid1 == -1) {
//         perror("Erreur de fork pour cmd1");
//         exit(EXIT_FAILURE);
//     }
//     if (pid1 == 0) 
// 	{
//         dup2(pipefd[1], STDOUT_FILENO);
//         close(pipefd[0]);  // On ferme la lecture du pipe
//         close(pipefd[1]);  // On ferme l'écriture du pipe après dup2
//         handle_redir_in_out(cmd1);
//         execve_cmd(NULL, cmd1);
//         perror("Erreur d'exécution cmd1");
//         exit(EXIT_FAILURE);
//     }
//     pid2 = fork();
//     if (pid2 == -1) {
//         perror("Erreur de fork pour cmd2");
//         exit(EXIT_FAILURE);
//     }
//     if (pid2 == 0) 
// 	{
//         dup2(pipefd[0], STDIN_FILENO);
//         close(pipefd[1]);
//         close(pipefd[0]);
//         handle_redir_in_out(cmd2);
//         execve_cmd(NULL, cmd2);
//         perror("Erreur d'exécution cmd2");
//         exit(EXIT_FAILURE);
//     }
//     close(pipefd[0]);
//     close(pipefd[1]);
//     waitpid(pid1, NULL, 0);
//     waitpid(pid2, NULL, 0);
// }


// void	exec_pipe_chain(t_data *data, t_cmd **cmd, t_env **env)
// {

//     t_cmd *tmp;

//     tmp = *cmd;
//     int i = 0;
// 	while (tmp != NULL)
// 	{
// 		if (tmp->next)
// 		{
//             printf("2\n");
// 			ft_handle_pipe_with_heredoc(tmp, tmp->matrice[i], data, env);
// 			tmp = tmp->next->next;
// 		}
// 		// else if(tmp->next)
// 		// {
// 		// 	ft_handle_pipe_with_heredoc(tmp, tmp->matrice[i], data, env);
// 		// 	tmp = tmp->next;
// 		// }
// 		else
// 		{
//             printf("1\n");
// 			exec_cmd(data, &tmp, env);
// 		}
// 	}
// }

