/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarico <almarico@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:11:39 by spagliar          #+#    #+#             */
/*   Updated: 2024/11/11 22:39:40 by almarico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Fonction pour lire du stdin jusqu'à un mot spécifique pour le heredoc
// donc ligne par ligne jusqu au delimiteur
// ecrit chaque ligne dans un fichier tant que le delimiteur n est pas atteint
bool	read_in_stdin(t_data *data, int fd, t_cmd *cmd)
{
	char		*line;

	(void) data;
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (false);
		if (strcmp(line, cmd->delimiter) == 0)
		{
			free(line);
			break ;
		}
		write (fd, line, strlen(line));
		write (fd, "\n", 1);
		free (line);
	}
	return (true);
}

/*
Cette fonction avance dans une chaîne de caractères en sautant les redirections (<, >) et
 les espaces. Elle est utilisée pour ignorer les caractères de redirection et les charges associées.
*/

void	pass_redirection_and_payload(char **line, int *i)
{
	while ((*line)[*i] && ((*line)[*i] == '<' || (*line)[*i] == '>'))
		*i += 1;
	while ((*line)[*i] && ft_isspace((*line)[*i]) == 0)
		*i += 1;
	while ((*line)[*i] && ft_isspace((*line)[*i]) != 0
		&& (*line)[*i] != '<' && (*line)[*i] != '>')
		*i += 1;
	if ((*line)[*i] != '\0' && (*line)[*i] != '<' && (*line)[*i] != '>')
		*i += 1;
}

/*
Cette fonction extrait une portion d'une chaîne de caractères entre deux indices,
en tenant compte des guillemets et des redirections. Elle peut également concaténer
des morceaux de chaîne si nécessaire
*/
void	exec_trim(char **line, char **res, int *i, int j)
{
	char	*sub_str;
	char	*tmp;

	tmp = NULL;
	if (*res != NULL)
	{
		tmp = ft_strdup(*res);
		free(*res);
		*res = NULL;
	}
	while ((*line)[*i] && (*line)[*i] != '<' && (*line)[*i] != '>')
		*i += 1;
	sub_str = ft_substr((*line), j, (*i - j));
	if ((*line)[*i] == '\0')
		*res = ft_strjoinn(tmp, sub_str);
	else if ((*line)[*i] && ft_is_in_quote((*line), *i) == FALSE
		&& ft_is_in_doublequote((*line), *i) == FALSE)
		*res = ft_strjoinn(tmp, sub_str);
	free(tmp);
	free(sub_str);
	pass_redirection_and_payload(line, i);
}
/*
Cette fonction est le gestionnaire principal qui parcourt toute la chaîne, en supprimant les
redirections tout en réassemblant le texte restant.
*/

void	trim_redirections(char **line)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = NULL;
	while ((*line)[i])
	{
		j = i;
		exec_trim(line, &res, &i, j);
	}
	if (res)
	{
		free((*line));
		(*line) = ft_strdup(res);
		free(res);
	}
}
