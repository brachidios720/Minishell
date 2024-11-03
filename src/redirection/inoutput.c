/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inoutput.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pag <pag@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:38:18 by spagliar          #+#    #+#             */
/*   Updated: 2024/11/03 09:55:04 by pag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
//manipule les decripteurs de fichiers entree / sortie suivant 2 conditions

//nb de redirection d'entree
int count_nb_redir_input(t_cmd *cmd)
{
	int i;
	if (!cmd->input_files || !cmd->input_files[0])
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
	
	i = 0;
	last_fd = STDIN_FILENO;  // Initialiser à STDIN_FILENO par défaut
	//si o -> aucune redir ->terminal
	 if (!cmd->input_redir || !cmd->input_redir[0])
		return (STDIN_FILENO);
	nb = count_nb_redir_input(cmd);
	while (i < nb )
	{
		//si redirection standard ->ouvre le fichier en lecture
		if (cmd->input_redir[i] == 1)
			tmp = open(cmd->input_files[i], O_RDONLY);
		//si redirection heredoc ->gestion avec apl de fonction
		else if (cmd->input_redir[i] == 2) //redirection heredoc
		{
			printf("redir heredoc detectee pour le fichier : %s\n", cmd->input_files[i]);
			tmp = here_doc(data, cmd->input_files[i]);
		}
		//des erreurs au moment de l ouverture
		if (tmp == -1)
		{
			perror ("erreor d ouevrture de fichier pour redir input");
			if (last_fd != -1 && last_fd != STDIN_FILENO)
                close(last_fd);
            return (-1);
        }
        // Redirige STDIN_FILENO vers le descripteur actuel
        if (dup2(tmp, STDIN_FILENO) == -1)
		{
            perror("Erreur de redirection d'entrée avec dup2 vers stdin");
            close(tmp);
            if (last_fd != -1 && last_fd != STDIN_FILENO)
                close(last_fd);
            return (-1);
        }
		close (tmp); //FERME TMP APRES DUP2
        // Ferme le descripteur précédent (sauf pour STDIN_FILENO)
        if (last_fd != -1 && last_fd != STDIN_FILENO)
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
	if (!cmd->output_files || !cmd->output_files[0])
		return (0); //pas de fichiers de sortie
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
	
	i = 0;
	last_fd = STDOUT_FILENO;
	//si o -> aucune redir ->terminal
	if (!cmd->output_redir || !cmd->output_redir[0])
		return (STDOUT_FILENO);
	nb = count_nb_redir_output(cmd);//compte le nbre de redirections de sortie
	while (i < nb )
	{
		//souvre le fichier en fonction du type de redirection
		if (cmd->output_redir[i] == 1)//redir standard (ecrasement)
			tmp = open(cmd->output_files[i], O_WRONLY | O_CREAT | O_TRUNC,0777);
		//si redirection heredoc																				
		else if (cmd->output_redir[i] == 2)//redirection avec ajout append
			tmp = open(cmd->output_files[i], O_WRONLY | O_CREAT | O_APPEND,0777);
		//si erreur au moment de l ouverture
		if (tmp == -1)
		{
			perror ("erreur d ouverture de fichier pour redir de sortie");
			if (last_fd != -1 && last_fd!= STDOUT_FILENO)
                close(last_fd);
            return (-1);
        }
        // Redirige STDOUT_FILENO vers le descripteur actuel
        if (dup2(tmp, STDOUT_FILENO) == -1)
		{
            perror("Erreur de redirection de sortie avec dup2");
            close(tmp);
            if (last_fd != -1 && last_fd != STDOUT_FILENO)
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
/*
//gestion des redirections d entree et sortie pour une commande
void handle_redir_inoutput(t_cmd *cmd, t_data *data)
{
	cmd->input_fd = handle_redir_input(cmd, data);
	cmd->output_fd = handle_redir_output(cmd);
	if (cmd->input_fd == -1 && cmd->output_fd != -1)
	{
		if (cmd->input_fd != STDIN_FILENO)
			close (cmd->input_fd);
	}
	if (cmd->output_fd == -1 && cmd->input_fd != -1)
	{
		if (cmd->output_fd != STDOUT_FILENO)
			close (cmd -> output_fd);
	}
}
*/
