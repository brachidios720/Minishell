/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:38:18 by spagliar          #+#    #+#             */
/*   Updated: 2024/10/16 14:38:20 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
//manipule les decripteurs de fichiers entree / sortie suivant 2 conditions
void	handle_redir_in_out(t_cmd **cmd)
{
	
	int	fd_in;
	int	fd_out;
	t_cmd *tmp = *cmd;
	if (tmp->infile)
	{
		fd_in = open(tmp->infile, O_RDONLY);
		if (fd_in == -1)
		{
			printf("ffff\n");
			perror("Erreur ouverture fichier d'entrée");
			exit(EXIT_FAILURE);
		}
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (tmp->outfile)
	{
		if (tmp->append)
		{
			fd_out = open(tmp->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
			printf ("outfile 1 : %s\n", tmp->outfile);
		}
		else
		{
			fd_out = open(tmp->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			printf ("outfile 2 : %s\n", tmp->outfile);
		}
		if (fd_out == -1)
		{
			perror("Erreur ouverture fichier de sortie");
			exit(EXIT_FAILURE);
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}