/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:53:41 by spagliar          #+#    #+#             */
/*   Updated: 2024/09/09 15:53:43 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//ajoute un nouveau noeud en fin de liste chainee
void	ft_lstadd_back_list(t_env **env, t_env *new_node)//ptr sur ptr de liste / ptr nouv noeud
{
	t_env	*endnode;

	if (*env == NULL) //si vide
	{
		*env = new_node; //new_node devient le 1er element 
		return ;
	}
	endnode = *env;//si pas vide on init endnode avec le premier element
	while (endnode->next) //parcourt tant qu on est pas a endnode
	{
		endnode = endnode->next;
	}
	endnode -> next = new_node; //si fin on pointe sur le nouveau
}
//creation d un nouveau noeud
t_env	*ft_env_new(char **envp, int i)
{
	t_env	*newnode;
	

	newnode = malloc(sizeof(t_env));
	if (!newnode)
		return (NULL);
	newnode->content = ft_strdup(envp[i]);
	//printf("%s\n", newnode);
	newnode->next = NULL;
	return (newnode);
}

//creation d une liste chainee de variable ex:  MY_VAR="Pag"
t_env	*init_env(char **envp)
{
	t_env *env_list; //ptr debut de liste qui a les variables 
    int i; //index

	env_list = NULL;
	i = 0;
	if (!envp)
		return NULL;
    while (envp[i])
    {
		t_env *new_node = ft_env_new(envp, i);
        if (new_node)
            ft_lstadd_back_list(&env_list, new_node);//ajout si reussite
        i++;
    }
    return (env_list);
}
//retourne chaque noeud qui represente une var d environnement