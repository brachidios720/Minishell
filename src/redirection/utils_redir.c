/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarico <almarico@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:22:05 by spagliar          #+#    #+#             */
/*   Updated: 2024/11/11 17:21:44 by almarico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//compte le nombre de redirections d'entrée pour une commande donnée.
// int count_nb_redir_input(t_cmd *cmd)
// {
// 	int i;
// 	if (!cmd->input_files || !cmd->input_files[0])
// 		return (0);
// 	i = 0;
// 	while(cmd->input_files[i])
// 		i++;
// 	printf("je suis dans count nb redir input et i = %d\n", i);
// 	//retourne le nbre total de fichiers d'entrée spécifiés dans cmd->input_files.
// 	return (i);
// }
//
//compte le nombre de redirections de sortie pour une commande spécifique.
// int count_nb_redir_output(t_cmd *cmd)
// {
// 	int i;
// 	if (!cmd->output_files || !cmd->output_files[0])
// 		return (0); //pas de fichiers de sortie
// 	i = 0;
// 	while(cmd->output_files[i])
// 		i++;
// 	printf("je suis dans count nb redir output et i = %d\n", i);
// 	//renvoie le nombre de fichiers de sortie définis dans cmd->output_files.
// 	return (i);
// }
