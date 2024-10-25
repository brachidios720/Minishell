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
//manipule les descripteurs de fichiers entree / sortie suivant 2 conditions
void	handle_redir_in_out(t_cmd *cmd)
{
	int	fd_in;
	int	fd_out;
	printf("n\n");
	if (cmd->infile)
	{
		//printf ("infile : %s\n", cmd->infile);
		fd_in = open(cmd->infile, O_RDONLY);
		printf ("infile open : %d\n", cmd->infile);
		if (fd_in == -1)
		{
			perror("Erreur ouverture fichier d'entrée");
			exit(EXIT_FAILURE);
		}
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (cmd->outfile)
	{
		printf ("outfile : %d\n", cmd->outfile);
		if (cmd->append)
		{
			fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
			printf ("outfile 1 : %d\n", cmd->outfile);
		}
		else
		{
			fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			printf ("outfile 2 : %d\n", cmd->outfile);
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