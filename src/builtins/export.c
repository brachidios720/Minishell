/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pag <pag@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:53:41 by spagliar          #+#    #+#             */
/*   Updated: 2024/11/11 15:21:08 by pag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
//si je tape export -> affichage de l'env

void	export_with_nothing(t_env *env)
{
	t_env	*ptr; //parcourt la liste chainee
	//char *tmp; //stock le contenu de la variable pour chaque noeud
	ptr =	env; //assigne ptr en debut de liste
	while (ptr)
	{
		printf ("declare -x %s\n", ptr->content);//print la var d environnement
		ptr = ptr->next; //passe au noeud suivant
	}
}

void	export_with_variable(t_env **env, char *new_var)
{
	t_env	*ptr; //parcourt la liste
	t_env	*new_node; //creation ny noeud
	ptr = *env; //init ptr avec le 1er element
	while (ptr)
	{
		if (ft_strncmp(ptr->content, new_var, ft_strchr(new_var, '=') - new_var) == 0)
		{
			free(ptr->content); //on libere l ancienne
			ptr->content = ft_strdup(new_var); // Mis a jour de la valeur d env
			return ;
		}
		ptr = ptr->next;
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->content = ft_strdup(new_var);
	new_node->next = NULL;
	if (*env == NULL)
		*env = new_node;// Si liste vide, on init avec la nouvelle variable
	else
	{
		ptr = *env;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new_node;// Ajout à la fin de la liste
	}
}

void	ft_export(t_env **env, char **args)//cf parsing
{
	int	i;

	if (!args[1])
		export_with_nothing(*env);
	else
	{
		i = 1; //apres export qui est 0
		while (args[i]) //si argu
		{
			export_with_variable(env, args[i]);
			i++;
		}
	}
}
//export MY_VAR="Pag" :
//args[0] -> export
//args 1  -> MY_VAR=PAG
//ARGS 2  -> NULL
