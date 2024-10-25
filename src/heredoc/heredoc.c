/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:38:12 by spagliar          #+#    #+#             */
/*   Updated: 2024/10/25 09:38:14 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void ft_handle_read_in_stdin(t_cmd *cmd, int pipefd[2])
{
    pid_t pid1;
    
    pid1 = fork();

    if (pid1 == 0)
    {
        // Rediriger la sortie standard vers le côté écriture du pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        //execute la 1ere cmd av pipe
        execve_cmd(NULL, cmd);
        // si echec execve
        perror("execve_cmd");
        exit(EXIT_FAILURE);
    }
        //att fin processus enfant (parent) 
        waitpid(pid1, NULL, 0);
}
//injecion du heredoc + exec 2nd cmd
void ft_exec_second_cmd_with_heredoc(t_cmd *cmd, char *delimiter, int pipefd[2])
{
    pid_t pid2;

    pid2 = fork();
    if (pid2 == 0)
    {
        //ferme le cote ecriture du pipe cf au dessus
        close (pipefd[1]);
        // Rediriger l'entrée standard depuis le pipe
        dup2(pipefd[0], STDIN_FILENO);
        // Injecter le heredoc dans l'entrée standard
        char *line;
        while(1)
        {
            line = readline(" > ");
            if (!line || strcmp(line, delimiter) == 0)
            {
                free(line);
                break;
            }
            write(STDIN_FILENO, line, strlen(line)); //ecrire dans stdin
            write(STDIN_FILENO, "\n", 1);
            free(line);
        }
        close(pipefd[0]); //fermer le pipe apres injection du heredoc
        //execute la 2nd cmd
        execve_cmd(NULL, cmd);
        perror("execve_cmd");
        exit(EXIT_FAILURE);
    }
    //Att fin du 2nd processus enfant (parent)
    waitpid(pid2, NULL,0);
}
//apl les deux fonctions pour gerer l"utilisation globale du pipeline
void ft_handle_pipe_with_heredoc(t_cmd *cmd, char *delimiter)
{
    int pipefd[2];
    // Créer un pipe
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return;
    }
    // apl 1re commande avec redirection de la sortie dans le pipe
    ft_exec_first_cmd_with_pipe(cmd, pipefd);
    // Si une cmd suit->gestion du heredeoc
    if (cmd->next)
    {
        ft_exec_second_cmd_with_heredoc(cmd->next, delimiter, pipefd);
    }

    // Fermer les descripteurs du pipe dans le parent
    close(pipefd[0]);
    close(pipefd[1]);
}
