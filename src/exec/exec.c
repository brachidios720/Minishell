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

//gestion de l envirionnement et execution + conversion
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
    cmd->matrice = prepare_argv(cmd, data->path);
    if (!cmd->matrice)
    {
        perror("Erreur de préparation des arguments");
        free(data->path);
        return;
    }

    // Gérer l'exécution et les redirections
    exec_with_env_and_redir(cmd, data);
}

bool	exec_cmd(t_data *data, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	if (cmd->next != NULL)
	{
		handle_pipe(cmd, cmd->next);
		return (true);
	}
	pid = fork();
	if (pid < 0)
	{
		printf ("error fork");
		return (false);
	}
	else if (pid == 0)
		execve_cmd(data, cmd);
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data->last_exit_status = WEXITSTATUS(status);
	}
	return (true);
}

bool	exec(t_data *data, t_cmd **cmd)
{
	t_cmd	*tmp;
	int		pip[2];

	tmp = *cmd;
	if (tmp && tmp->str)
	{
		if (data->pipe)
		{
			if (pipe(pip) == -1)
				return (false);
		}
		exec_cmd(data, tmp);
	}
	return (true);
}
