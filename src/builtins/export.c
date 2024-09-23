/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:53:41 by spagliar          #+#    #+#             */
/*   Updated: 2024/09/09 15:53:43 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

//Gere export sans arguments
bool	export_no_args(char **copy_env, int len)
{
	int	i;
	int	j;

	i = 0;
	if (!copy_env)
		return (false);
	sort_array(copy_env, len); //tri le tan env avant de l'afficher
	while (i < len)
	{
		printf("declare -x");
		j = 0;
		while (copy_env[i][j] != '\0' && copy_env[i][j] != '=' )//affiche la vari jusqu a '='
		{
			printf ("%c", copy_env[i][j]);
			j++;
		}
		if (copy_env[i][j] != '\0' && copy_env[i][j] == '=')//affiche la valeur apres '=' si la
		{
			printf ("=%s\"\n", &copy_env[i][j + 1]);
		}
		else
			printf ("\n");
		i++;
	}
	return (true);
}
//verifie si la variable existe deja dans l environnement
int	exist(char *argv, char **copy_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (argv[i] && argv[i] != '=')//parcourt jusqu a trouver '=' iu la fin
		i++;
	while (copy_env[j] != NULL)//parcourt env pour verif si existe
	{
		if (!ft_strncmp(copy_env[j], argv, strlen(argv))
			&& (copy_env[j][i] == '\0' || copy_env[j][i] == '='))
			return (j);//retour index si trouve
		j++;
	}
	return (-1);
}
//ajoute ou met a jour une variable d environnement
char	**export_comm(char *argv, char **copy_env)
{
	int		len;
	int		pos;
	char	*value;
	char	**new_env;
	int		i;

	len = 0;
	pos = exist(argv, copy_env);//verif si existe
	value = ft_strdup(argv);
	if (!value)
	{
		printf("Erreur d'alloc pour %s\n", argv);
		return (NULL);
	}
	printf("Position de %s dans l'env: %d\n", argv, pos);
	if (pos >= 0)
	{
		//si la variable existe, on la remplace
		 printf("Remplacement de la variable existante: %s\n", copy_env[pos]);
		free((copy_env)[pos]);
		(copy_env)[pos] = value;
		return (copy_env);
	}
	else
	{
		//calcule de la taille actuelle de l env
		while ((copy_env)[len] != NULL)
			len++;
		//alloc pour un nouv tab pour eviter le triple pointeur et inclure la nouv var
		new_env = malloc((len + 2) * sizeof(char *));
		if (!new_env)
		{
			free (value);
			return (NULL);
		}
		i = 0;
		while ((copy_env)[i])
		{
			new_env[i] = (copy_env)[i];
			printf("Copie de la variable existante: %s\n", new_env[i]);
			i++;
		}
		new_env[i] = value;
		printf("Ajout de la nouvelle variable: %s\n", new_env[i]);
		new_env[i + 1] = NULL;
		//libere l ancien tab mais pas les chaines pointees
		printf("Libération de l'ancien tableau copy_env (sans les variables)\n");
		free(copy_env);
	}
	return (new_env);
}
//gere a commande export
int	ft_export(char **argv, char **copy_env)
{
	int	exit;
	int	i;
	int	len;

	exit = 0;
	i = 1;
	len = 0;
	while ((copy_env)[len])//calcule la longueur de l env
	{
		printf("%s\n", copy_env[len]);
		len++;
	}
	printf("\n\n\n\n\n\n\n");
	printf("longueur : %d\n", len);
	
	if (!argv || !argv[i])
	{
		//si aucun argument passe a export
		if (copy_env && !export_no_args(copy_env, len))
			return (-1);
		return (0);
	}
	//boucle pour tous les arguments passes
	char **new_env;
	while (argv[i])
	{
		//printf("traite l'argument : %s\n", argv[i]);
		if (!check_id(argv[i]))
		{
			//printf("id invalide pour : %s\n", argv[i]);
			exit = 1;//si id invalide
		}
		else
		{
            new_env = export_comm(argv[i], copy_env);
            if (!new_env)
			{
				//printf("erreur lors de l'export de %s\n", argv[i]);
                return (-1);
			}
			copy_env = new_env;  // Mise à jour du tableau d'environnement
			printf("export reussi de : %s\n", argv[i]);
        }
        i++;
	}
	i = 0;
	while(new_env[i])
	{
		printf("new_env : %s\n", new_env[i]);
		i++;
	}
    return (exit);
}