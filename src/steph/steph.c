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

    if (dup2(infile_fd, STDIN_FILENO) == -1) 
    {
        perror("Erreur de redirection d'entrée");
        exit(EXIT_FAILURE);
    }

    if (handle_redir_output(cmd) == -1)  // Redirige la sortie vers fichier si spécifié
    {
        perror("Erreur redirection de sortie");
        exit(EXIT_FAILURE);
    }

    close(pipe_fd[0]);  // Ferme l'extrémité de lecture du pipe
    if (infile_fd != STDIN_FILENO)
        close(infile_fd);  // Ferme le descripteur d'entrée si ouvert spécifiquement
}

void	ft_pipe_middle_cmd(int prev_fd, int pipe_fd[2], t_cmd *cmd)
{
    (void)cmd;
    if (prev_fd != -1 && dup2(prev_fd, STDIN_FILENO) == -1)
    {
        perror("Erreur redirection d'entrée");
        exit(EXIT_FAILURE);
    }
    close(prev_fd);  // Ferme l'extrémité précédente après redirection

    if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)  // Redirige la sortie vers le pipe actuel
    {
        perror("Erreur redirection sortie");
        exit(EXIT_FAILURE);
    }

    close(pipe_fd[1]);  // Ferme l'extrémité d'écriture du pipe
    close(pipe_fd[0]);  // Ferme l'extrémité de lecture du pipe
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

        // Crée un pipe si une commande suivante existe
        if (tmp->next != NULL && pipe(pipe_fd) == -1)
        {
            perror("Pipe error");
            exit(EXIT_FAILURE);
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
            execute_command_or_builtin(&tmp, env, data);
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