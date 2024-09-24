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
	int		i;
	int		j;
	char	**tabl;

	tabl = lst_to_arr(env); // conv list en tab
	if (!tab)
		return (false);
	sort_arr(tabl, len_list(env)); // tri les var par ordre alpha
	i = 0;
	while (tab[i])
	{
		printf("declare -x "); //aff bash pour l export ds l env != var locale
		j = 0;
		while (tabl[i][j] && tabl[i][j] != '=') //affiche jusqu a =
			printf("%c", tabl[i][j++]);
		// Si la variable a une valeur, l'afficher avec des guillemets
		if (tabl[i][j] && tabl[i][j] == '=')
			printf("=\"%s\"\n", &tabl[i][j + 1]);
		else
			// Si la variable n'a pas de valeur, sauter à la ligne
			printf("\n");
		i++;
	}
	free(tab);
	return (true);
}
//verif si la syntax des noms de variables d'env est valide -> cf shell
bool	valid_id(char *str)
{
	int i;

	i = 0;
	if ((!str[0] || str[0] != '_') && !ft_isalpha(str[0]))//verif 1st car ni alphab ni _
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')//verif si ni alphanum ni _
			return (false);
		i++;
	}
	return (true);
}
//verif si la variable existe deja dans l env et retourne sa positio si existe ou -1
int	exist(char *str, t_env *env)
{
	int i;
	int j;
	t_env *tmp;

	if(!env)
		return (-1);//env est vide -> var n existe pas
	i = 0;
	while (str[i] && str[i] != '=')//trouve la longueur de nom de la variable stop a =
		i++;
	j = 0;
	tmp = env; //init tmp debut de la liste env
	 while (tmp)
    {
        char *content = (char *)tmp->content;
        if (!ft_strncmp(content, str, i) && (content[i] == '\0' || content[i] == '='))
        {
            return (j); // la variable existe, retourne sa position
        }
        tmp = tmp->next;
        j++;
    }
    return (-1); // la variable n'existe pas dans la liste
}
//ajoute ou met a jour la variable
bool	export_var(char *str, t_data *data)
{
	int		pos;//stock la position de la variable
	char	*copy;//ptr stock copy de la chaine
	t_env	*env_ptr;//parcourt la liste chainee des var d environnemtn

	pos = exist(str, data->env);// veirf si var existe
	copy = ft_strdup(str);//cree 1 copy la chiane d entree
	if (!copy)
		return (false);
	if (pos >= 0) //si la var existe deja
	{
		env_ptr = data->env;
		while (pos > 0)
		{
			env_ptr = env_ptr->next;
			pos--;
		}
		free(env_ptr->content);
		env_ptr->content = copy;
	}
	else if (pos == -1) //si elle n existe pas
	{
		t_env *new_node = malloc(sizeof(t_env));
		if(!new_node)
		{
			free(copy);
			return (false);
		}
		new_node->content = copy;
		new_node->next = data->env;
		data->env = new_node;
	}
	return (true);
}

//fction principale gere la commande export
int	ft_export(char **str, t_data *data)
{
	int	exit_code; //code de sortie
	int	i; //index

	exit_code = 0;
	i = 1; //demarre au premier argumen apres la commande
	if (!str || !str[i]) //if null or no args
	{
		if (data->env && !export_no_args(data->env)) //aff env
			return (-1); //error
		return (0);
	}
	while (str[i])// boucle sur chaque argument
	{
		if (!valid_id(str[i])) // if invalide
		{
			printf("export_var: invalid id\n");
			exit_code = 1;
		}
		else if (!export_var(str[i], data))// si valide ->exporte la variable
			return (-1);//si error
		i++;
	}
	return (exit_code);//retourne le code de sortie final
}