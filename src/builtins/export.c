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
bool	export_no_args(t_env *env)
{
	char	**tab;
	int		i;
	int		j;

	tab = lst_to_tab(env); // con list en tab
	if (!tab)
		return (false);
	sort_tab(tab, len_tab(env)); // tri les var par ordre alpha
	i = 0;
	while (tab[i])
	{
		printf("declare -x "); //affiche declare av chaque var
		j = 0;
		while (tab[i][j] && tab[i][j] != '=') //affiche jusqu a =
			printf("%c", tab[i][j++]);
		// Si la variable a une valeur, l'afficher avec des guillemets
		if (tab[i][j] && tab[i][j] == '=')
			printf("=\"%s\"\n", &tab[i][j + 1]);
		else
			// Si la variable n'a pas de valeur, sauter à la ligne
			printf("\n");
		i++;
	}
	free(tab);
	return (true);
}
