/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <spagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:14:51 by spagliar          #+#    #+#             */
/*   Updated: 2024/11/08 13:14:52 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pipe_first_cmd(int pipe_fd[2], t_cmd *cmd, t_data *data)
{
    int infile_fd;

    infile_fd = handle_redir_input(cmd, data);
    if (infile_fd == -1)
    {
        perror("Erreur de redirection d'entrée");
        exit(EXIT_FAILURE);
    }

	if (infile_fd != STDIN_FILENO)
    {
        if (dup2(infile_fd, STDIN_FILENO) == -1)
        {
            perror("Erreur redirection d'entrée");
            exit(EXIT_FAILURE);
        }
    }
    if (handle_redir_output(cmd) == -1)  // Redirige la sortie vers fichier si spécifié
    {
        perror("Erreur redirection de sortie");
        exit(EXIT_FAILURE);
    }
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)  // Redirige sortie vers le pipe
    {
        perror("Erreur redirection sortie");
        exit(EXIT_FAILURE);
    }
	close(pipe_fd[0]);  // Ferme l’extrémité de lecture du pipe
    if (infile_fd != STDIN_FILENO)
        close(infile_fd);  // Ferme le descripteur d'entrée si ouvert spécifiquement
}

void ft_pipe_last_cmd(int pipe_fd[2], t_cmd *cmd, t_data *data)
{
    int infile_fd;

    infile_fd = handle_redir_input(cmd, data);
    if (infile_fd == -1) 
    {
        perror("Erreur de redirection d'entrée");
        exit(EXIT_FAILURE);
    }
    if (infile_fd != STDIN_FILENO)  // Si un fichier d'entrée est spécifié
    {
        dup2(infile_fd, STDIN_FILENO);
        close(infile_fd);
    }
    else  // Sinon, redirige depuis l'extrémité de lecture du pipe précédent
    {
        dup2(pipe_fd[0], STDIN_FILENO);
    }
    // if (dup2(infile_fd, STDIN_FILENO) == -1) 
    // {
    //     perror("Erreur de redirection d'entrée");
    //     exit(EXIT_FAILURE);
    // }
    close(pipe_fd[0]);  // Ferme l'extrémité de lecture du pipe
    if (handle_redir_output(cmd) == -1)  // Redirige la sortie vers fichier si spécifié
    {
        perror("Erreur redirection de sortie");
        exit(EXIT_FAILURE);
    }
    if (infile_fd != STDIN_FILENO)
        close(infile_fd);  // Ferme le descripteur d'entrée si ouvert spécifiquement
}

void	ft_pipe_middle_cmd(int prev_fd, int pipe_fd[2], t_cmd *cmd)
{
    (void)cmd;
    if (prev_fd != -1)
    {
        dup2(prev_fd, STDIN_FILENO);  // Redirige l'entrée standard vers le pipe précédent
        close(prev_fd);
    }  // Ferme l'extrémité précédente après redirection

    dup2(pipe_fd[1], STDOUT_FILENO);  // Redirige la sortie standard vers le nouveau pipe
    close(pipe_fd[1]);  // Ferme l'extrémité d'écriture du pipe
    close(pipe_fd[0]);   // Ferme l'extrémité de lecture du pipe
}

void exec_pipe_chain(t_data *data, t_cmd **cmd, t_env **env)
{
    pid_t pid;
    t_cmd *tmp = *cmd;
    int pipe_fd[2];         // Pipe pour chaque commande
    int command_index = 0;
    int prev_fd = -1;       // Fichier de l'extrémité de lecture du pipe précédent

    while (tmp != NULL)
    {
        //printf("Executing command: %s\n", tmp->str);
        if(is_builtin_parent(tmp->str))
            execute_builtin_in_parent(tmp, env);
        else
        {
        // Crée un pipe si une commande suivante existe
            if (tmp->next != NULL && pipe(pipe_fd) == -1)
            {
                perror("Pipe error");
                exit(EXIT_FAILURE);
            }
        }
        pid = fork();
        if (pid == -1)
        {
            perror("Fork error");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)  // Processus enfant
        {
            if (command_index == 0)  // Première commande
            {
                //printf("Première commande - redirection de sortie vers pipe\n");
                ft_pipe_first_cmd(pipe_fd, tmp, data);
            }
            else if (tmp->next == NULL)  // Dernière commande
            {
                //printf("Dernière commande - redirection de lecture depuis pipe\n");
                ft_pipe_last_cmd((int[2]){prev_fd, pipe_fd[1]}, tmp, data);
            }
            if (tmp->next != NULL && tmp != *cmd) // Commande intermédiaire
			{
                //printf("Commande intermédiaire - redirection entre pipes\n");
    			ft_pipe_middle_cmd(prev_fd, pipe_fd, tmp);
			}
            
            // Exécuter la commande (builtin ou externe)
            execute_command_or_builtin(&tmp, env);
            exit(EXIT_SUCCESS);
        }
        else  // Processus parent
        {
            if (prev_fd != -1)
                close(prev_fd);       // Ferme l'extrémité de lecture précédente

            close(pipe_fd[1]);        // Ferme l'extrémité d'écriture actuelle pour le parent
            prev_fd = pipe_fd[0];     // Définir l'extrémité de lecture actuelle pour la prochaine commande

            waitpid(pid, NULL, 0);    // Attend que le processus enfant se termine

            command_index++;
        }
        
        tmp = tmp->next;
    }
}

int is_builtin_parent(const char *command) 
{
    return (ft_strcmp(command, "export") == 0 || 
            ft_strcmp(command, "unset") == 0 || 
            ft_strcmp(command, "cd") == 0);
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