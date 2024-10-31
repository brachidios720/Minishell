/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inoutput.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pag <pag@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:38:18 by spagliar          #+#    #+#             */
/*   Updated: 2024/10/31 11:43:57 by pag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
//manipule les decripteurs de fichiers entree / sortie suivant 2 conditions

//nb de redirection d'entree
int count_nb_redir_input(t_cmd *cmd)
{
	int i;
	if (cmd->input_files)
		return (0);
	i = 0;
	while(cmd->input_files[i])
	{
		i++;
	}
	return (i);
}
//gestion des redirections d'entree suivant le type
int handle_redir_input(t_cmd *cmd, t_data *data)
{
	int nb;
	int i;
	int tmp;
	int last_fd;
	
	//si o -> aucune redir ->terminal
	if (!cmd->input_redir[0])
		return (STDIN_FILENO);
	nb = count_nb_redir_input(cmd);
	i = 0;
	last_fd = -1;
	while (i < nb )
	{
		//si redirection standard ->ouvre le fichier en lecture
		if (cmd->input_redir[i] == 1)
			tmp = open(cmd->input_files[i], O_RDONLY);
		//si redirection heredoc ->gestion avec apl de fonction
		else if (cmd->input_redir[i] == 2)
			tmp = here_doc(data, cmd->input_files[i]);
		//si erreur au moment de l ouverture
		if (tmp == -1)
		{
			perror ("erreor d ouevrture de fichier pour redir input");
			if (last_fd != STDIN_FILENO)
                close(last_fd);
            return (-1);
        }
        // Redirige STDIN_FILENO vers le descripteur actuel
        if (dup2(tmp, STDIN_FILENO) == -1)
		{
            perror("Erreur de redirection d'entrée avec dup2");
            close(tmp);
            if (last_fd != STDIN_FILENO)
                close(last_fd);
            return (-1);
        }
        // Ferme le descripteur précédent (sauf pour STDIN_FILENO)
        if (last_fd != STDIN_FILENO)
            close(last_fd);
        // Sauvegarde le descripteur actuel pour la prochaine boucle
        last_fd = tmp;
        i++;
    }
    // Retourne le dernier descripteur redirigé
    return (last_fd);
}
int count_nb_redir_output(t_cmd *cmd)
{
	int i;
	if (cmd->output_files)
		return (0);
	i = 0;
	while(cmd->output_files[i])
	{
		i++;
	}
	return (i);
}

//gestion des redirections d'entree suivant le type
int handle_redir_output(t_cmd *cmd)
{
	int nb;
	int i;
	int tmp;
	int last_fd;
	
	//si o -> aucune redir ->terminal
	if (!cmd->input_redir[0])
		return (STDIN_FILENO);
	nb = count_nb_redir_output(cmd);
	i = 0;
	last_fd = -1;
	while (i < nb )
	{
		//si redirection standard ->ouvre le fichier en ecriture
		if (cmd->output_redir[i] == 1)
			tmp = open(cmd->output_files[i], O_WRONLY | O_CREAT | O_TRUNC,0777);
		//si redirection heredoc																				
		else if (cmd->output_redir[i] == 2)
			tmp = open(cmd->output_files[i], O_WRONLY | O_CREAT | O_APPEND,0777);
		//si erreur au moment de l ouverture
		if (tmp == -1)
		{
			perror ("erreur d ouverture de fichier pour redir de sortie");
			if (last_fd != STDOUT_FILENO)
                close(last_fd);
            return (-1);
        }
        // Redirige STDOUT_FILENO vers le descripteur actuel
        if (dup2(tmp, STDOUT_FILENO) == -1)
		{
            perror("Erreur de redirection de sortie avec dup2");
            close(tmp);
            if (last_fd != STDOUT_FILENO)
                close(last_fd);
            return (-1);
        }
        // Ferme le descripteur précédent
        if (last_fd != STDOUT_FILENO)
            close(last_fd);
        // Sauvegarde le descripteur actuel pour la prochaine boucle
        last_fd = tmp;
        i++;
    }
    // Retourne le dernier descripteur redirigé
    return (last_fd);
}
