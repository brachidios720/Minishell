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
	if (cmd->input)
	{
		//printf ("infile : %s\n", cmd->infile);
		fd_in = open(cmd->infile_path, O_RDONLY);
		printf ("infile open : %s\n", cmd->infile_path);
		if (fd_in == -1)
		{
			perror("Erreur ouverture fichier d'entrée");
			exit(EXIT_FAILURE);
		}
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (cmd->output)
	{
		printf ("outfile : %s\n", cmd->outfile_path);
		if (cmd->append)
		{
			fd_out = open(cmd->outfile_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
			printf ("outfile 1 : %s\n", cmd->outfile_path);
		}
		else
		{
			fd_out = open(cmd->outfile_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			printf ("outfile 2 : %s\n", cmd->outfile_path);
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