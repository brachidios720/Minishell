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

//gère une seule redirection d'entrée.
//vérifie le type de redirection (1 pour fichier, 2 pour heredoc).
int handle_single_input_redir(t_cmd *cmd, t_data *data)
{
	int	i;
    int fd;
    
	i = 0;
	//pour fichier -> elle ouvre le fichier en lecture seule.
    if (cmd->input_redir[i] == 1)
        fd = open(cmd->input_files[i], O_RDONLY);
	//pour heredoc -> apl la fonction here_doc
    else if (cmd->input_redir[i] == 2)
    {
        printf("redir heredoc detectee pour le fichier : %s\n", cmd->input_files[i]);
        fd = here_doc(data, cmd->input_files[i]);
    }
	//si le type est inconnu -> erreur
    else
    {
        // Gestion d'erreur pour un type de redirection inconnu
        fprintf(stderr, "Type de redirection inconnu\n");
        return -1;
    }
    //verif si l ouverture du fichier a reussi
    if (fd == -1)
    {
		perror("Erreur d'ouverture de fichier pour redir input");
		return (-1);
	}
   	//retourne le descripteur
	return (fd);
}

//gere les redirections d'entree suivant le type de redirection pour une cmd
int handle_redir_input(t_cmd *cmd, t_data *data)
{
    int nb;
    int i;
    int tmp;
    int last_fd;
    
    i = 0;
    last_fd = STDIN_FILENO;
	//verif si presence des redirections d'entrée.
    if (!cmd->input_redir || !cmd->input_redir[0])
        
		return (STDIN_FILENO);
	//apl la fonction pour compter le nb de redirections d entree
    nb = count_nb_redir_input(cmd);
    while (i < nb)
    {
		//Pour chaque redirection -> apl de fonction
        tmp = handle_single_input_redir(cmd, data);
        if (tmp == -1)
        {
            if (last_fd != -1 && last_fd != STDIN_FILENO)
                close(last_fd);
            return (-1);
        }
		//rediriger l'entrée standard vers le fichier ouvert.
        if (dup2(tmp, STDIN_FILENO) == -1)
        {
			//gere les erreurs et ferme le descripteir
            perror("Erreur de redirection d'entrée avec dup2 vers stdin");
            close(tmp);
            if (last_fd != -1 && last_fd != STDIN_FILENO)
                close(last_fd);
            return (-1);
        }
        close(tmp);
        if (last_fd != -1 && last_fd != STDIN_FILENO)
            close(last_fd);
        last_fd = tmp;
        i++;
    }
	//retourne le dernier descripteur de fichier utilisé.
    return (last_fd);
}

int handle_single_output_redir(t_cmd *cmd, int index)
{
    int fd;
    
    if (cmd->output_redir[index] == 1)
        fd = open(cmd->output_files[index], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    else if (cmd->output_redir[index] == 2)
        fd = open(cmd->output_files[index], O_WRONLY | O_CREAT | O_APPEND, 0777);
    else
    {
        // Gestion d'erreur pour un type de redirection inconnu
        fprintf(stderr, "Type de redirection de sortie inconnu\n");
        return -1;
    }
    
    if (fd == -1)
        perror("Erreur d'ouverture de fichier pour redir de sortie");
    return fd;
}

int handle_redir_output(t_cmd *cmd)
{
    int nb;
    int i;
    int tmp;
    int last_fd;
    
    i = 0;
    last_fd = STDOUT_FILENO;
    
    if (!cmd->output_redir || !cmd->output_redir[0])
        return (STDOUT_FILENO);
    nb = count_nb_redir_output(cmd);
    while (i < nb)
    {
        tmp = handle_single_output_redir(cmd, i);
        if (tmp == -1)
        {
            if (last_fd != -1 && last_fd != STDOUT_FILENO)
                close(last_fd);
            return (-1);
        }
        if (dup2(tmp, STDOUT_FILENO) == -1)
        {
            perror("Erreur de redirection de sortie avec dup2");
            close(tmp);
            if (last_fd != -1 && last_fd != STDOUT_FILENO)
                close(last_fd);
            return (-1);
        }
        if (last_fd != STDOUT_FILENO)
            close(last_fd);
        last_fd = tmp;
        i++;
    }
    return (last_fd);
}
