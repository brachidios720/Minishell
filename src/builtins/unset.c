/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*      unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:50:03 by spagliar          #+#    #+#             */
/*   Updated: 2024/09/09 16:50:05 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//si je tape unset MY_VAR -> delete dans l env
void unset_with_variable(t_env **env, char *my_var)
{
    t_env **ptr;//pointeur vers un pointeur
    t_env *tmp; //init un ptr temporaire qui parcourt la liste
    char *pos;//position du caractere "="
    int len_name;//longeur du nom "my_var" jusqu a =
    //rappel : content = contenu
    ptr = env; //ptr est place en tete de la liste chainee
    
    while(*ptr)
    {
        pos = ft_strchr((*ptr)->content, '=');
        if(pos)// si position -> =
            len_name = pos - (*ptr)->content;
        if (ft_strncmp((*ptr)->content, my_var, len_name) == 0 && my_var[len_name] == '\0')
        {
            tmp = *ptr;//sauvegarde le noeud actuel
            *ptr = (*ptr)->next;
            free(tmp->content);
            free(tmp);
            return;
        }   
        ptr = &((*ptr)->next);
    }
}

int ft_unset(t_env **env, char **args)
{
    int i;

    if (!args[1])
    {
        return (1);
    }
    i = 1; //unset = args[0]
    while (args[i]) //cf parsing
    {
        printf("arg: %s\n", args[i]);
        unset_with_variable(env, args[i]);
        i++;
        printf("arg: %s\n", args[i]);
    }
    return (0);
}
