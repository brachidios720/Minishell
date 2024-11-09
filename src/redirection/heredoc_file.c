/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <spagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:16:43 by spagliar          #+#    #+#             */
/*   Updated: 2024/11/09 16:19:37 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//verifie si le delimiteur doit etre extrait
//gestion du heredoc en créant un fichier temporaire->ouverture pour ecrire les donnees
//envoi un descripteur pour etre lu ou erreur -> apl de read_input_with_heredoc

int ft_heredoc(t_cmd *cmd, t_data *data)
{
    int tmp_fd;
    // Ouvrir un fichier temporaire pour le here-document
    tmp_fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, MODE_HEREDOC);
    if (tmp_fd == -1)
    {
        perror("Erreur lors de l'ouverture du fichier temporaire");
        return -1;
    }
    read_input_with_heredoc(tmp_fd, cmd);
    close(tmp_fd);
    return (0);
}
