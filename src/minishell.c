/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pag <pag@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:54:54 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/11/13 16:33:13 by pag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
affiche l'invite perso du shell
utilise les codes d'echappement pour les couleurs av et apres pour init
*/

void	print_minishell(void)
{
	printf("\033[32m ##   ##    ##                ##\
	              ###                ###      ###        ###    ####\033[0m\n");
	printf("\033[32m ### ###                        \
	              ##                 ##       ##       ####   ##  ##\033[0m\n");
	printf("\033[32m #######   ###     #####     ### \
	     #####    ##       ####      ##       ##      ## ##       ##\033[0m\n");
	printf("\033[32m #######    ##     ##  ##     ## \
	    ##        #####   ##  ##     ##       ##     ##  ##     ###\033[0m\n");
	printf("\033[32m ## # ##    ##     ##  ##     ## \
	    #####    ##  ##  ######     ##       ##     #######   ##\033[0m\n");
	printf("\033[32m ##   ##    ##     ##  ##     ## \
	       ##   ##  ##  ##         ##       ##         ##   ##  ##\033[0m\n");
	printf("\033[32m ##   ##   ####    ##  ##    ####\
	  ######   ###  ##   #####    ####     ####        ##   ######\033[0m\n");
}

/*
Ce fichier constitue la base de l’interface de boucle du shell
gestion : les données clés, l'affichage, et la libération de mémoire avant la sortie. 
l54->struct principale du shell
l55->struct pour les cmd
l56->stuct pour les var d'env
l62->affiche l'invite de commande
l63->allocation memoire
l69->initialise les var d'env en fonction de envp cf tab de var d'env init env
l70->on ajoute pwd pour configurer le repertoire de travail initial
l71->apl de la fonction qui prend la boucle principale d'execution du shell
l72->free cmd et data
*/

int	main(int ac, char **av, char **envp)//nbr d'argument + var d'env
{
	t_data	*data;
	t_cmd	*cmd;
	t_env	*env;

	data = NULL;
	cmd = NULL;
	env = NULL;
	(void)ac;
	(void)av;
	print_minishell();
	data = malloc(sizeof(t_data));
	cmd = malloc(sizeof(t_cmd));
	if (data == NULL || cmd == NULL)
	{
		perror("Erreur d'allocation mémoire pour data");
		return (1);
	}
	env = init_env(envp);
	init_pwd(&env);
	ft_check_line(data, &cmd, &env);
	free (cmd);
	free (data);
	return (0);
}
