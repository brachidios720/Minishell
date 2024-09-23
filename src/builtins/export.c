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


//export apl sans args -> affiche les var d'environnement attendu
bool export_no_args(t_env *env)
{
	char	**arr;
	int		i;
	int		j;

	// Convertir la liste chaînée t_env en tableau de chaînes de caractères
	arr = lst_to_arr(env);
	if (!arr)
		return (false);

	// Trier les variables d'environnement par ordre alphabétique
	sort_array(arr, len_list(env));

	i = 0;
	while (arr[i])
	{
		// Afficher "declare -x " avant chaque variable
		printf("declare -x ");
		j = 0;

		// Afficher le nom de la variable jusqu'au signe '='
		while (arr[i][j] && arr[i][j] != '=')
			printf("%c", arr[i][j++]);

		// Si la variable a une valeur, l'afficher avec des guillemets
		if (arr[i][j] && arr[i][j] == '=')
			printf("=\"%s\"\n", &arr[i][j + 1]);
		else
			// Si la variable n'a pas de valeur, sauter à la ligne
			printf("\n");

		i++;
	}

	// Libérer la mémoire allouée pour le tableau
	free(arr);

	return (true);
}
