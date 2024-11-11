/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pag <pag@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:14:10 by spagliar          #+#    #+#             */
/*   Updated: 2024/11/09 19:30:15 by pag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

//gère une seule redirection d'entrée.
//vérifie le type de redirection (1 pour fichier en lecture seule, 2 pour heredoc).
//retourne un descripteur de fichier ou -1 si erreur
int handle_single_input_redir(t_cmd *cmd, t_data *data)
{
    (void)data;
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
        fd = ft_heredoc(cmd, data);
    }
	//si le type est inconnu -> erreurarg
    else
    {
        // Gestion d'erreur pour un type de redirection inconnu
        ft_printf("Type de redirection inconnu cfsingle input\n");
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
//gere plusieurs redirection d entree pour une cmd
//apl count_nb_redir_imput -> pour compter les redirections
//gere chaque redir en utilisant open ou ft_heredoc
//retourne le dernier descripteur ouvert ou -1
int handle_redir_input(t_cmd *cmd, t_data *data)
{
    int nb; //nbre de redirection
    int i;
    int tmp; //var tmp pour fd
    int last_fd; //dernier file decriptor
    
    i = 0;
    last_fd = STDIN_FILENO;
	// verif si presence des redirections d'entrée.
    if (!cmd->input_redir || !cmd->input_redir[0])
		return (STDIN_FILENO);
	// apl la fonction pour compter le nb de redirections d entree
    nb = count_nb_redir_input(cmd);
    while (i < nb)
    {
        printf("IIIIIIIIIIIIIIII\n");
		if (cmd->input_redir[i] == 1)
			tmp = open(cmd->input_files[i], O_RDONLY);
		else if (cmd->input_redir[i] == 2)
			tmp = ft_heredoc(cmd, data);
		if (i != 0)
			close(last_fd);
		if (tmp == -1)
			return (-1);
		last_fd = tmp;
		i++;
	}
	//retourne le dernier descripteur de fichier utilisé.
	return (tmp);
}

//gere une seule redirection de sortie
//si type 1 -> fichier en mode ecriture si 2 fichier en mode ajout/ecrase
//retourne le descripteur de fichier ou -1 en cas d erreur
int handle_single_output_redir(t_cmd *cmd, int index)
{
    int fd;
    
    if (cmd->output_redir[index] == 1)
        fd = open(cmd->output_files[index], O_WRONLY | O_CREAT | O_TRUNC, READ_WRITE_EXEC);
    else if (cmd->output_redir[index] == 2)
        fd = open(cmd->output_files[index], O_WRONLY | O_CREAT | O_APPEND, READ_WRITE_EXEC);
    else
    {
        // Gestion d'erreur pour un type de redirection inconnu
        ft_printf("Type de redirection de sortie inconnu cfsingle ouput\n");
        return -1;
    }
    if (fd == -1)
        perror("Erreur d'ouverture de fichier pour redir de sortie");
    return fd;
}
//gere plusieurs redirection de sortie
//compte les redirections ->count_nb_redir_output
//applique chaque redrection et utilise dupe pour rediriger la sortie standard
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

