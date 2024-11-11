/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarico <almarico@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:14:10 by spagliar          #+#    #+#             */
/*   Updated: 2024/11/11 14:10:48 by almarico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

//gère une seule redirection d'entrée.
//vérifie le type de redirection (1 pour fichier en lecture seule, 2 pour heredoc).
//retourne un descripteur de fichier ou -1 si erreur
static int handle_single_input_redir(t_cmd *cmd, t_data *data, int i)
{
    int fd;
    
    
	//pour fichier -> elle ouvre le fichier en lecture seule.
    if (cmd->redir_type[i] == INPUT_FILE)
        fd = open(cmd->payload[i], O_RDONLY);
	//pour heredoc -> apl la fonction here_doc
    else if (cmd->redir_type[i] == HEREDOC)
	{
		cmd->delimiter = ft_strdup(cmd->payload[i]);
        fd = ft_heredoc(cmd, data);
	}
   	//retourne le descripteur
	return (fd);
}
//gere plusieurs redirection d entree pour une cmd
//apl count_nb_redir_imput -> pour compter les redirections
//gere chaque redir en utilisant open ou ft_heredoc
//retourne le dernier descripteur ouvert ou -1
// static int	handle_redir_input(t_cmd *cmd, t_data *data)
// {
//     int i;
//     int tmp; //var tmp pour fd
//     int last_fd; //dernier file decriptor
//
//     i = 0;
//     last_fd = STDIN_FILENO;
//     while (i < nb)
//     {
// 		if (cmd->input_redir_type == INPUT_FILE)
// 			tmp = open(cmd->input_files[i], O_RDONLY);
// 		else if (cmd->input_redir == HEREDOC)
// 			tmp = ft_heredoc(cmd, data);
// 		if (i != 0)
// 			close(last_fd);
// 		if (tmp == -1)
// 			return (-1);
// 		i++;
// 	}
// 	last_fd = tmp;
// 	//retourne le dernier descripteur de fichier utilisé.
// 	return (tmp);
// }

// int handle_redir_input(t_cmd *cmd, t_data *data)
// {
//     int nb; //nbre de redirection
//     int i;
//     int tmp; //var tmp pour fd
//     int last_fd; //dernier file decriptor
//     
//     i = 0;
//     last_fd = STDIN_FILENO;
// 	//verif si presence des redirections d'entrée.
//     if (!cmd->input_redir || !cmd->input_redir[0])
//     {
//         printf("jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj");
// 		return (STDIN_FILENO);
// 	//apl la fonction pour compter le nb de redirections d entree
//     }
//     nb = count_nb_redir_input(cmd);
//     printf("nb = %d\n", nb);
//     while (i < nb)
//     {
// 		if (cmd->input_redir_type == INPUT_FILE)
// 			tmp = open(cmd->input_files[i], O_RDONLY);
// 		else if (cmd->input_redir == HEREDOC)
// 			tmp = ft_heredoc(cmd, data);
// 		if (i != 0)
// 			close(last_fd);
// 		if (tmp == -1)
// 			return (-1);
// 		i++;
// 	}
// 	last_fd = tmp;
// 	//retourne le dernier descripteur de fichier utilisé.
// 	return (tmp);
// }
//gere une seule redirection de sortie
//si type 3 -> fichier en mode ecriture si 4 fichier en mode ajout/ecrase
//retourne le descripteur de fichier ou -1 en cas d erreur
int handle_single_output_redir(t_cmd *cmd, int index)
{
    int fd;
    
    if (cmd->redir_type[index] == OUTPUT_FILE)
        fd = open(cmd->payload[index], O_WRONLY | O_CREAT | O_TRUNC, READ_WRITE_EXEC);
    else if (cmd->redir_type[index] == APPEND)
        fd = open(cmd->payload[index], O_WRONLY | O_CREAT | O_APPEND, READ_WRITE_EXEC);
    return fd;
}
//gere plusieurs redirection de sortie
//compte les redirections ->count_nb_redir_output
//applique chaque redrection et utilise dupe pour rediriger la sortie standard
// int handle_redir_output(t_cmd *cmd)
// {
//     int nb;
//     int i;
//     int tmp;
//     int last_fd;
//     
//     i = 0;
//     last_fd = STDOUT_FILENO;
//     
//     if (!cmd->output_redir || !cmd->output_redir[0])
//         return (STDOUT_FILENO);
//     nb = count_nb_redir_output(cmd);
//     while (i < nb)
//     {
//         tmp = handle_single_output_redir(cmd, i);
//         if (tmp == -1)
//         {
//             if (last_fd != -1 && last_fd != STDOUT_FILENO)
//                 close(last_fd);
//             return (-1);
//         }
//         if (dup2(tmp, STDOUT_FILENO) == -1)
//         {
//             perror("Erreur de redirection de sortie avec dup2");
//             close(tmp);
//             if (last_fd != -1 && last_fd != STDOUT_FILENO)
//                 close(last_fd);
//             return (-1);
//         }
//         if (last_fd != STDOUT_FILENO)
//             close(last_fd);
//         i++;
//     }
//     last_fd = tmp;
//     return (last_fd);
// }

void	handle_redirection(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	while (cmd->redir_type[i] != -1)
	{
		if (cmd->redir_type[i] == INPUT_FILE || cmd->redir_type[i] == HEREDOC)
			cmd->input_fd = handle_single_input_redir(cmd, data, i);
		else if (cmd->redir_type[i] == OUTPUT_FILE || cmd->redir_type[i] == APPEND)
			cmd->output_fd = handle_single_output_redir(cmd, i);
		i++;
	}
}
