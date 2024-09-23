/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:53:41 by spagliar          #+#    #+#             */
/*   Updated: 2024/09/09 15:53:43 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*Objectif : creer une copy du tab de chaine de caractere
Role de la fonction : retourne une copy de notre environement
dans le tableau d'origine*/


/*Objectif : trier les chaines du tab pour les mettre par ordre croissant
Role de la fonction : tableau trie -> faciliter recherche et lecture*/
void sort_array(char **env, int len)
{
	int i; //index chaine 1
	int j; //index chaine 2
	int result; //resultat de comparaison des deux chaines
	char *temp;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1; //j = chaine suivante de i a comparer avec i dans le meme tableau
		while (j < len)
		{
			result = ft_strncmp(env[i], env[j], INT_MAX); //compare avec une taille max de chaine
			if (result > 0) //si result positif
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
}

//objectif : verif syntax identifiant -> unset et export
//si chaine vide
//si 1 er caractere n est ni _ ou une lettre alpha(minimaxi)
bool	check_id(char *argv)
{
	int	i;

	if (!ft_isalpha(argv[0]) && argv[0] != '_')
	{
		return (false);
	}
	i = 0;
	while (argv[i])
	{
		if (!ft_isalnum(argv[i]) && argv[i] != '_')
		{
			return (false);
		}
		i++;
	}
	return (true);
}

//recherche la variable ds env
int	search_var(char *argv, char **env)
{
	int		i;//size
	int		j;//position ds le tableau

	if (!env) //si NULL
	{
		return (-1);
	}
	i = strlen(argv);
	j = 0;
	// Parcourir le tableau env
	while (env[j] != NULL)
	{
		// Si la variable est trouvée (comparaison jusqu'au '=')
		if (!ft_strncmp(env[j], argv, i) && env[j][i] == '=')
		{
			return (j);// Retourne la position de la variable
		}
		j++;
	}
	return (-1);// Si la variable n'est pas trouvée
}

char *ft_strncpy(char *s1, char *s2, int n)
{
	int i = 0;
	while(s1[i] && i < n)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return(s2);
}
