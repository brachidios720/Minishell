/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:58:25 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/09 16:52:44 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_exit(int i)
{
	if(i == 1)
		printf("args error\n");
	exit(0);
}


int ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	while(s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return((unsigned int )s1[i] - (unsigned int)s2[i]);
}

void    print_minishell(void)
{
	printf("\033[32m ##   ##    ##                ##              ###                ###      ###        ###    ####\033[0m\n");
	printf("\033[32m ### ###                                       ##                 ##       ##       ####   ##  ##\033[0m\n");
	printf("\033[32m #######   ###     #####     ###      #####    ##       ####      ##       ##      ## ##       ##\033[0m\n");
	printf("\033[32m #######    ##     ##  ##     ##     ##        #####   ##  ##     ##       ##     ##  ##     ###\033[0m\n");
	printf("\033[32m ## # ##    ##     ##  ##     ##      #####    ##  ##  ######     ##       ##     #######   ##\033[0m\n");
	printf("\033[32m ##   ##    ##     ##  ##     ##          ##   ##  ##  ##         ##       ##         ##   ##  ##\033[0m\n");
	printf("\033[32m ##   ##   ####    ##  ##    ####    ######   ###  ##   #####    ####     ####        ##   ######\033[0m\n");
<<<<<<< Updated upstream
=======
}

/*Objectif : creer une copy du tab de chaine de caractere
Role de la fonction : retourne une copy de notre environement
dans le tableau d'origine*/

char	**ft_strdup_tab(char **env)
{
	char	**new_tab;
	int		i;
	int		len;

	len = 0;
	while (env[len]) //!= NULL
		len++;
	new_tab = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new_tab) //verif ok malloc
		return (NULL);
	i = 0;
	while (env[i]) //!= NULL
	{
		new_tab[i] = ft_strdup(env[i]); //attribut la copy
		if (!new_tab[i]) //si vide
		{
			free(new_tab);
			return (NULL);
		}
		i++;
	}
	new_tab[i] = NULL;//fin de copy
	return (new_tab);
}


char *ft_strcpy(char *s1 , char *s2)
{
    int i = 0 ;
    while(s2[i])
    {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = '\0';
    return(s1);
>>>>>>> Stashed changes
}