/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pag <pag@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:11:39 by spagliar          #+#    #+#             */
/*   Updated: 2024/11/09 17:47:40 by pag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Fonction pour lire du stdin jusqu'à un mot spécifique pour le heredoc
// donc ligne par ligne jusqu au delimiteur
// ecrit chaque ligne dans un fichier tant que le delimiteur n est pas atteint
bool read_in_stdin(t_data *data, int fd, t_cmd *cmd)
{
    (void)data;
    char    *line;

    while (1)
	{
        // Demande à l'utilisateur d'entrer une ligne
        line = readline("> ");
        if (!line) // Gestion de la fin de l'entrée
            return (false);
        // Comparaison de la ligne avec le mot de fin
        if (strcmp(line, cmd->delimiter) == 0)
        {
            free(line);
            break;
        }
        // Écrit la ligne dans le fichier `fd`
        write (fd, line, strlen(line));
        write (fd, "\n", 1); // Ajoute un saut de ligne après chaque entrée
        free (line);
    }
    return (true);
}
