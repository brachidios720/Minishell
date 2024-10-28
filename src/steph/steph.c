#include "../../include/minishell.h"

void	ft_pipe_first_cmd(int pipe_fd[2], t_cmd *cmd)
{
	if (cmd->infile != STDIN_FILENO)
		dup2(cmd->infile, STDIN_FILENO);  // Redirige l'entrée standard si un fichier est spécifié
	dup2(pipe_fd[1], STDOUT_FILENO);      // Redirige la sortie vers le pipe
	close(pipe_fd[0]);                    // Ferme l’extrémité de lecture du pipe
	close(pipe_fd[1]);
}


void	ft_pipe_middle_cmd(int pipe_fd[2], t_cmd *cmd)
{
	(void)cmd;
	dup2(pipe_fd[0], STDIN_FILENO);       // Redirige l'entrée depuis le pipe précédent
	if (cmd->outfile != STDOUT_FILENO)
        dup2(cmd->outfile, STDOUT_FILENO); // Redirige la sortie si un fichier de sortie est spécifié
	close(pipe_fd[0]);      // Redirige la sortie vers le nouveau pipe
	close(pipe_fd[1]);
}

void	ft_pipe_last_cmd(int pipe_fd[2], t_cmd *cmd)
{
	dup2(pipe_fd[0], STDIN_FILENO);       // Redirige l'entrée depuis le pipe
	if (cmd->outfile != STDOUT_FILENO)
		dup2(cmd->outfile, STDOUT_FILENO); // Redirige la sortie si un fichier de sortie est spécifié
	close(pipe_fd[0]);
	close(pipe_fd[1]);                    // Ferme l’extrémité d’écriture du pipe
}

void	ft_pipe(t_data *data, t_cmd *cmd, int pipe_fd[2])
{
	if (data->rien == TRUE)
	{              // Première commande
		printf ("1\n");
		ft_pipe_first_cmd(pipe_fd, cmd);
	}
	else if (cmd->next == NULL)    // Dernière commande
	{
		ft_pipe_last_cmd(pipe_fd, cmd);
		printf("2\n");
	}
	else                               // Commande intermédiaire
	{
		ft_pipe_middle_cmd(pipe_fd, cmd);
		printf("3\n");
	}
}

void	exec_pipe_chain(t_data *data, t_cmd **cmd, t_env **env)
{
	pid_t pid;
    t_cmd *tmp;
    tmp = *cmd;
	int pipe_fd[2];  // Pipe utilisé pour les redirections de chaque commande
	int command_index = 0;
	int prev_fd = -1;

	while (tmp != NULL)
	{
		printf("Executing command: %s\n", tmp->str);
		if (tmp->next != NULL && pipe(pipe_fd) == -1)
		{
            perror("Pipe error");
            exit(EXIT_FAILURE);
        }
		pid = fork();
		if (pid == -1)
		{
			printf("e\n");
			perror("Fork error");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)        // Processus enfant
		{
			if (command_index == 0)          // Première commande
            {
				printf("z\n");
				ft_pipe_first_cmd(pipe_fd, tmp);
			}
            else if (tmp->next == NULL)      // Dernière commande
            { 
				printf("d\n");
				ft_pipe_last_cmd((int[2]){prev_fd, pipe_fd[1]}, tmp);
			}
			else                             // Commande intermédiaire
			{
				printf("t\n");
                ft_pipe_middle_cmd((int[2]){prev_fd, pipe_fd[1]}, tmp);
			//ft_pipe(data, tmp, pipe_fd);  // Configure les pipes en fonction de la position
			}	
			execute_command_or_builtin(&tmp, env, data);        // Exécute la commande
			exit(EXIT_SUCCESS);
		}
		else    // Processus parent
        {
            if (prev_fd != -1)               // Ferme l'ancienne extrémité de lecture
                close(prev_fd);
			if(tmp->next != NULL)
			{
            	close(pipe_fd[1]);              // Ferme l'extrémité d'écriture pour le parent
			}
			prev_fd = pipe_fd[0];            // Préserve l'extrémité de lecture pour la prochaine commande
            waitpid(pid, NULL, 0);           // Attend la fin du processus enfant
            command_index++;
        }
        tmp = tmp->next;
	}
}