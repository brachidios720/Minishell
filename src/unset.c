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
//verif syntax identifiant

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
//recherche la variable ds env

void check_env(char *var_to_delete, char **env)
{
	int i;

	// Appel de search_var pour trouver l'index de la variable à supprimer
	i = search_var(var_to_delete, env);
	
	// Si la variable est trouvée (index != -1)
	if (i != -1)
	{
		// Libérer la mémoire de la variable d'environnement
		free(env[i]);

		// Décaler les variables suivantes pour combler l'espace vide
		while (env[i] != NULL)
		{
			env[i] = env[i + 1];
			i++;
		}
	}
}
//mettre a jour la liste avec un pointeur de pointeur env

bool	delete_var(char *argv, char **env)
{
	int i;
	int j;

	i = 0;
	// Rechercher la variable à supprimer dans l'environnement
	while (env[i] != NULL)
	{
		// Si la variable est trouvée (strncmp pour comparer jusqu'au '=')
		if (strncmp(env[i], argv, strlen(argv)) == 0 && env[i][strlen(argv)] == '=')
		{
			// Libérer la mémoire de la variable d'environnement
			free(env[i]);
			// Déplacer les éléments restants dans le tableau pour combler le trou
			j = i;
			while (env[j] != NULL)
			{
				env[j] = env[j + 1];
				j++;
			}
			// On a trouvé et supprimé la variable, donc on peut sortir
			return true;
		}
		i++;
	}
	// La variable n'a pas été trouvée dans l'environnement
	return false;
}

int ft_unset(char **argv, char **env)
{
	int i;  // On commence à 1 car argv[0] est généralement "unset"
	int ret;  // Code de retour, 0 signifie succès

	i =		1;
	ret =	0;
	// Parcourir toutes les variables passées dans argv
	while (argv[i] != NULL)
	{
		// Appeler check_env pour supprimer la variable
		if (search_var(argv[i], env) != -1)
		{
			check_env(argv[i], env);  // Supprime la variable
		}
		else
		{
			// Si la variable n'existe pas, on peut décider de retourner une erreur
			ret = 1;// Indique qu'il y a eu une erreur avec au moins une variable
		}
		i++;
	}
	// Retourner 0 si tout s'est bien passé, 1 si au moins une erreur
	return (ret);
}
