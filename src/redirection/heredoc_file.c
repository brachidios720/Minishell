/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarico <almarico@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:16:43 by spagliar          #+#    #+#             */
/*   Updated: 2024/11/09 20:06:51 by almarico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	replace_matrice_with_heredoc_file(t_cmd *cmd)
{
	int		index_matrice;
	int		i;
	char	**tmp_matrice;

	index_matrice = 0;
	while (cmd->matrice[index_matrice])
		index_matrice++;
	index_matrice -= 2;
	tmp_matrice = malloc((index_matrice + 1) * sizeof(char *));
	if (!tmp_matrice)
		return (-1);
	tmp_matrice[index_matrice] = NULL;
	tmp_matrice[0] = ft_strdup(cmd->matrice[0]);
	tmp_matrice[1] = ft_strdup("/tmp/heredoc_tmp");
	i = 2;
	index_matrice = 3;
	while (cmd->matrice[index_matrice])
		tmp_matrice[i++] = ft_strdup(cmd->matrice[index_matrice++]);
	ft_free_tab(cmd->matrice);
	cmd->matrice = ft_strdup_tab(tmp_matrice);
	ft_free_tab(tmp_matrice);
	return (0);
}

//verifie si le delimiteur doit etre extrait
//gestion du heredoc en créant un fichier temporaire->ouverture pour ecrire les donnees
//envoi un descripteur pour etre lu ou erreur -> apl de read_input_with_heredoc

int	ft_heredoc(t_cmd *cmd, t_data *data)
{
	int	tmp_fd;

	(void)data;
    // Ouvrir un fichier temporaire pour le here-document
	tmp_fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, MODE_HEREDOC);
	if (tmp_fd == -1)
	{
		perror("Erreur lors de l'ouverture du fichier temporaire");
		return (-1);
	}
	read_input_with_heredoc(tmp_fd, cmd);
	close(tmp_fd);
	if (replace_matrice_with_heredoc_file(cmd) == -1)
		return (-1);
	return (0);
}
