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
    t_env *ptr; //init un ptr qui parcourt la liste
    t_env *prev;
    char *pos;//position du caractere "="
    int len_name;//longeur du nom "my_var" jusqu a =
    //rappel : content = contenu
    ptr = *env; //ptr est place en tete de la liste chainee
    prev = NULL; //init un noeud precedent -> pour garder une trace
    pos = ft_strchr(ptr->content, '=');
    while(ptr)
    {
        if(pos)// si position -> =
            len_name = pos - ptr->content;
        if (ft_strncmp(ptr->content, my_var, len_name) == 0 && my_var[len_name] == '\0')
        {
            if (prev == NULL)
                *env = ptr->next;
            else
                prev->next = ptr->next;
            free(ptr->content);
            free(ptr);
            return;
        }
        prev = ptr;
        ptr = ptr->next;
    }
}

void ft_unset(t_env **env, char **args)
{
    int i;

    if (!args[1])
    {
        printf("no args\n");
    }
    i = 1; //unset = args[0]
    while (args[i])
    {
        printf("arg: %s\n", args[i]);
        unset_with_variable(env, args[i]);
        i++;
        printf("arg: %s\n", args[i]);
    }
}
