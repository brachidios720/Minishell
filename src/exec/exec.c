/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:53:41 by spagliar          #+#    #+#             */
/*   Updated: 2024/09/09 15:53:43 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//prepare le tableau argv en fonction des infos donnees dans cmd
char **prepare_argv(t_cmd *cmd, char *cmd_path)
{
	char **argv = malloc(sizeof(char *)*3); //3 elements
	if (!argv)
	{
		return (NULL);
	}
	argv[0] = cmd_path; //ls
	argv[1] = cmd->option; //-la
	argv[2] = NULL;

	return (argv);
}

//gestion de l execution d une commande avec les redirections et la variables d environnement
void exec_with_env_and_redir(t_cmd *cmd, t_data *data)
{
	char **envp;
	char *cmd_path = data->path;

// Conversion de la liste des variables d'environnement en tableau
    envp = env_list_to_array(data->copy_env);
    if (!envp)
    {
        perror("Erreur de conversion des variables d'environnement");
        free(cmd_path);
        return;
    }
    // Gérer les redirections (entrée/sortie)
    handle_redir_in_out(cmd);
    // Exécuter la commande avec execve
    if (execve(cmd_path, cmd->matrice, envp) == -1)
    {
        perror("Erreur execve");
        free(cmd_path);
        free(envp);
        exit(EXIT_FAILURE);
    }
    free(cmd_path);
    free(envp);
}

void execve_cmd(t_data *data, t_cmd *cmd)
{
    // Trouver le chemin complet de la commande et le stocker dans `data->path`
    data->path = find_command_path(cmd->matrice[0]);
	printf ("valeur :%s\n", data->path);
    if (!data->path)
    {
        printf("Commande non trouvée : %s\n", cmd->str);
        return;
    }

    // Préparer les arguments pour execve et les stocker dans cmd->matrice
    cmd->incmd = prepare_argv(cmd, data->path);
    if (!cmd->incmd)
    {
        perror("Erreur de préparation des arguments");
        free(data->path);
        return;
    }

    // Gérer l'exécution et les redirections
    exec_with_env_and_redir(cmd, data);
}
// gestion de l execution de commande soit directement soit via un pipe
void	exec_cmd(t_data *data, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		printf ("error fork");
		return;
	}
	else if (pid == 0)
	{
		handle_redir_in_out(cmd);
		execve_cmd(data, cmd);
		perror("erreur d execution de commande");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		data->last_exit_status = WEXITSTATUS(status);
	}
}
// Gestion globale de l'exécution des commandes et des pipes
bool	exec(t_data *data, t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = *cmd;
	while (tmp != NULL && tmp->str != NULL)
	{
		// Crée un pipe si nécessaire pour les commandes intermédiaires
		if (data->pip && tmp->next != NULL)
		{
			if (pipe(data->pipe_fd) == -1)
				return (false);
		}

		// Gestion de la position de la commande
		if (tmp == *cmd) // Première commande
			ft_pipe_first_cmd(data, tmp);
		else if (tmp->next == NULL) // Dernière commande
			ft_pipe_last_cmd(data, tmp);
		else // Commande intermédiaire
			ft_pipe_middle_cmd(data, tmp);

		// Exécute la commande actuelle
		exec_cmd(data, tmp);

		// Fermeture des descripteurs de pipe inutilisés
		if (data->pip)
		{
			close(data->pipe_fd[1]); // Ferme l'extrémité d'écriture après exécution
			data->read_fd_cmd = data->pipe_fd[0]; // Prépare la lecture pour la prochaine commande
		}

		tmp = tmp->next; // Passe à la commande suivante
	}
	return (true);
}


