/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pag <pag@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:14:51 by spagliar          #+#    #+#             */
/*   Updated: 2024/11/13 20:34:17 by pag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//gére la redirection des descripteurs de fichiers. Elle configure la redirection
//d'un descripteur source (src_fd) vers un descripteur de destination (dest_fd)
// et effectue un nettoyage en fermant les descripteurs inutilisés.
void	handle_redir_fd(int src_fd, int dest_fd)
{
	dprintf(2, "src_fd; %d\n", src_fd);
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
	printf("mmmmmmmmmmmmmm\n");
	while (!tmp)
	{
		pid = fork(); //debut processus child
		if (pid == -1)
		{
			perror("fork error\n");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			handle_redirection(tmp, data);
			handle_redir_fd(tmp->input_fd, tmp->output_fd);
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
/*
void	exec_pipe_chain(t_data *data, t_cmd **cmd, t_env **env)
{
	(void)data;
	pid_t	pid;
	t_cmd	*tmp;
	//int		pipe_fd[2];
	int		prev_fd;
	int		command_index;

	tmp = *cmd;
	prev_fd = -1;
	command_index = 0;
	
	while (tmp != NULL)
	{
		if (tmp->next != NULL && pipe(tmp->pipe_fd) == -1) // Crée un pipe si une commande suivante existe
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
		if (pid == 0)
		{
			if (command_index == 0 && tmp->next != NULL)
				ft_pipe_first_cmd(tmp->pipe_fd, tmp);
			else if (tmp->next == NULL)
				ft_pipe_last_cmd(tmp->pipe_fd, tmp);
			else
				ft_pipe_middle_cmd(prev_fd, tmp->pipe_fd);
			execute_command_or_builtin(&tmp, env, data);
			exit(EXIT_SUCCESS);
		}
		else //processus parent
		{
			//if (prev_fd != -1)//ferme l extrmite de lecture precedente
			//	close(prev_fd);
			//close(tmp->pipe_fd[1]);//ferme l extrmite actuelle du pipe
			prev_fd = tmp->pipe_fd[0];//prepare prev pr la cmd suivante
			waitpid(pid, NULL, 0); //fin processus enfant
			command_index++;//incremente l index des commandes
		}
		tmp = tmp->next;//cmd suivante
	}
	// if (prev_fd != -1)
	// {
	// 	if (close(prev_fd) == -1)
	// 		perror("Erreur lors de la fermeture finale de prev_fd");
	// }
}
//Configure la redirection pour la 1ere cmd dans un pipe
void	ft_pipe_first_cmd(int pipe_fd[2], t_cmd *cmd)
{
	if (cmd->input_fd == -1)
	{
		perror("Erreur de redir d'entrée pour pipe 1rst cmd : %d\n");
		exit(EXIT_FAILURE);
	}
	handle_redir_fd(cmd->input_fd, STDIN_FILENO);//redirige l entree
	handle_redir_fd(pipe_fd[1], STDOUT_FILENO);//redirige la sortie vers l extrmite d ecriture du pipe
	//if (close(pipe_fd[0]) == -1)//ferme l extrmite non utilisee
	//{
	//	perror("Erreur a la fermeture du pipe");
	//}
}

//Configure la redirection pour la dernière commande dans un pipeline.
void	ft_pipe_last_cmd(int pipe_fd[2], t_cmd *cmd)
{
	if (cmd->input_fd == -1)
	{
		perror("Erreur de redirection d'entrée pour pipe last cmd");
		exit(EXIT_FAILURE);
	}
	if (cmd->input_fd != -1) //signifie qu un fichier a ete specifie comme source d entree
		handle_redir_fd(cmd->input_fd, STDIN_FILENO); //Redirige l entree standard vers ce fichier
	else
		handle_redir_fd(pipe_fd[0], STDIN_FILENO); //sinon la cmd doit lireles infos qui vient du pipe
		//pas de fermeture le parent s en charge
}

//Configure la redirection pour une commande intermédiaire dans un pipeline.
void	ft_pipe_middle_cmd(int prev_fd, int pipe_fd[2])
{
	handle_redir_fd(prev_fd, STDIN_FILENO); // Redirige l'entrée depuis le pipe précédent
	handle_redir_fd(pipe_fd[1], STDOUT_FILENO); // Redirige la sortie vers l'extrémité d'écriture du pipe
	//pas de fermeture car utilise ds prochaine cmd
}

void	exec_pipe_chain(t_data *data, t_cmd **cmd, t_env **env)
{
    pid_t pid;
    t_cmd *tmp = *cmd;
    int pipe_fd[2];         // Pipe pour chaque commande
    int command_index = 0;
    int prev_fd = -1;       // Fichier de l'extrémité de lecture du pipe précédent

    while (tmp != NULL)
    {
        if(is_builtin_parent(tmp->str))
            execute_builtin_in_parent(tmp, env);
        else
        {
            if (tmp->next != NULL && pipe(pipe_fd) == -1) // Crée un pipe si une commande suivante existe
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
            
            //ft_chaine_pipe_utils(pipe_fd, cmd, data, command_index);
            if (command_index == 0 && tmp->next != NULL)  // Première commande
               ft_pipe_first_cmd(pipe_fd, tmp, data);
            else if (tmp->next == NULL)  // Dernière commande
                ft_pipe_last_cmd((int[2]){prev_fd, pipe_fd[1]}, tmp, data);
            if (tmp->next != NULL && tmp != *cmd) // Commande intermédiaire
    			ft_pipe_middle_cmd(prev_fd, pipe_fd, tmp);
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
}*/

/*
void	ft_pipe_first_cmd(int pipe_fd[2], t_cmd *cmd, t_data *data)
{
	int	infile_fd;

	(void)data;
	infile_fd = cmd->input_fd;
	if (infile_fd == -1)
	{
		perror("Erreur de redirection d'entrée si infile_fd == -1");
		exit(EXIT_FAILURE);
	}
	if ((infile_fd != STDIN_FILENO) && (dup2(infile_fd, STDIN_FILENO) == -1))
	{
		perror("Erreur redirection d'entrée");
		exit(EXIT_FAILURE);
	}
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("Erreur redirection sortie");
		exit(EXIT_FAILURE);
	}
	close (pipe_fd[0]);
	if (infile_fd != STDIN_FILENO)
		close(infile_fd);
}
 ->Configure la redirection pour la première commande dans un pipeline.
	Redirige l'entrée standard si un fichier d'entrée est spécifié (cmd->input_fd).
	Redirige la sortie standard vers l'extrémité d'écriture du pipe (pipe_fd[1]).
	Ferme l'extrémité inutilisée du pipe.

void	ft_pipe_last_cmd(int pipe_fd[2], t_cmd *cmd, t_data *data)
{

	(void)data;
	infile_fd = cmd->input_fd;
	if (infile_fd == -1)
	{
		perror("Erreur de redirection d'entrée");
		exit(EXIT_FAILURE);
	}
	if (infile_fd != STDIN_FILENO)
	{
		dup2(infile_fd, STDIN_FILENO);
		close(infile_fd);
	}
	else
	{
		dup2(pipe_fd[0], STDIN_FILENO);
	}
	close(pipe_fd[0]);
	if (infile_fd != STDIN_FILENO)
		close(infile_fd);
}
	->Configure la redirection pour la dernière commande dans un pipeline.
	Redirige l'ent.stand depuis l'extrémité de lect du pipe précéd. (pipe_fd[0]).
	Si un fichier d'entrée est spécifié, il est utilisé à la place du pipe.
	Ferme les descripteurs inutilisés.

void	ft_pipe_middle_cmd(int prev_fd, int pipe_fd[2], t_cmd *cmd)
{
	(void)cmd;
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
}
	->Configure la redirection pour une commande intermédiaire.
	Redirige l'entrée standard depuis le pipe précédent (prev_fd).
	Redirige la sortie standard vers l'extrémité d'écriture du pipe actuel (pipe_fd[1]).
	Ferme les descripteurs inutilisés.
*/