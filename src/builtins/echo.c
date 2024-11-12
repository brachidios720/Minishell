/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarico <almarico@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:45:23 by spagliar          #+#    #+#             */
/*   Updated: 2024/11/12 00:15:33 by almarico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
//gestion de l option -n
bool	echo_n(char *argv)
{
	int	i;

	if (argv[0] != '-' && argv[1] != 'n')
	{
		return (false);
	}
	i = 0;
	while (argv[i])
	{
		if (argv[i] == '-' && argv[i + 1] == 'n')
			return (true);
		if (argv[i] == '-' && argv[i + 1] == '-')
			return (false);
		i++;
	}
	return (true);
}

char	*ft_itoa_m(int n)
{
	char	buff[12];
	long	nb;
	int		i;
	int		negatif;

	i = 0;
	nb = (long)n;
	negatif = 0;
	if (!nb)
		return (ft_zero());
	if (nb < 0)
	{
		negatif = 1;
		nb = -nb;
	}
	while (nb)
	{
		buff[i++] = (nb % 10) + 48;
		nb /= 10;
	}
	if (negatif)
		buff[i++] = '-';
	buff[i] = '\0';
	return (ft_return(buff));
}

// char *expand_variable(char *arg, t_data *data, t_env **env)
// {
// 	//printf("arg = %s\n", arg);
//     if (arg[0] == '$') 
// 	{
//         if (arg[1] == '?') 
//             return (ft_itoa_m(data->last_exit_status)); 
// 		else if(search_in_env(env, arg) == 0)
//             return (getenv(arg + 1));  // Cherche la variable d'environnement sans le '$'
// 		else
// 			ft_strdup("");
//     }
//     return (arg);  // Retourner l'argument tel quel s'il ne s'agit pas d'une variable
// }

char *ft_strjoinn(char const *s1, char const *s2)
{
    size_t len1 = 0;
    size_t len2 = 0;
    char *strj;

    if (s1) len1 = ft_strlen(s1);  // S'assurer que s1 n'est pas NULL
    if (s2) len2 = ft_strlen(s2);  // S'assurer que s2 n'est pas NULL

    strj = malloc(len1 + len2 + 1);
    if (strj == NULL)
        return NULL;

    if (s1) ft_memcpy(strj, s1, len1);  // Copier s1 si ce n'est pas NULL
    if (s2) ft_memcpy(strj + len1, s2, len2);  // Copier s2 si ce n'est pas NULL

    strj[len1 + len2] = '\0';  // Ajouter le caractère de fin de chaîne
    return strj;
}

char *ft_strjoin_char(char *s1, char c) {
    int len;
    char *result;

    if (s1 != NULL)
        len = strlen(s1);
    else
        len = 0;

    result = malloc(len + 2);  // +2 pour le caractère et le '\0'
    if (result == NULL)
        return NULL;

    if (s1 != NULL)
        strcpy(result, s1);
    
    result[len] = c;
    result[len + 1] = '\0';

    free(s1);  // Libère s1 si elle a été allouée dynamiquement
    return result;
}

// char *expand_variables_in_string(char *str) {
//     char *result = NULL;
//     char *temp;
//     int i = 0;
//     int start;
//     char *var_name;
//     char *var_value;

//     while (str[i] != '\0') {
//         if (str[i] == '$') {  // Détecte le début d'une variable
//             i++;
//             start = i;
//             while (str[i] != '\0' && ft_isalpha(str[i]) == 1) {
//                 i++;
//             }

//             var_name = ft_substr(str, start, i - start); // Extraire le nom de la variable
//             var_value = getenv(var_name);    // Recherche la variable dans `t_env`
//             if(var_value == NULL)
// 				var_value = "";

//             //temp = ft_strjoin(result, var_value);      // Concatène la valeur de la variable
// 			//temp = result;
// 			result = ft_strjoin(result, var_value); 
// 			//free(result);
//             //result = temp;
//             free(var_name);
//         } else {
//             //temp = result;
//             result = ft_strjoin_char(result, str[i]);    // Ajoute chaque caractère individuel
//             //free(result);
//             i++;
//         }
//     }
//     return result;
// }

char *last_exit(t_data *data)
{
	char *value;
	//i += 2;

	value = ft_itoa_m(data->last_exit_status);
	return(value);

}

char *expand_variables_in_string(char *str, t_data *data) 
{
    char *result = NULL;
    int i = 0;
    int start;
    char *var_name;
    char *var_value;

    while (str[i] != '\0') {
		if(str[i] == '$' && str[i + 1] == '?')
		{
			result = last_exit(data);
			i += 2;
		}
        if (str[i] == '$') {  // Détecte le début d'une variable
			i++;
            start = i;
            while (str[i] != '\0' && ft_isalpha(str[i]) == 1) {
                i++;
            }

            var_name = ft_substr(str, start, i - start);  // Extrait le nom de la variable

            // Recherche la valeur de la variable dans l'environnement
            var_value = getenv(var_name); 
            if (var_value == NULL) {
                var_value = "";  // Si la variable n'est pas trouvée, remplace par une chaîne vide
            }
            result = ft_strjoinn(result, var_value);  // Concatène la chaîne
            free(var_name);  // Libère le nom de la variable
        } else {
            // Si ce n'est pas une variable, on ajoute le caractère au résultat
     		result = ft_strjoin_char(result, str[i]);    // Ajoute chaque caractère individuel
            i++;
        }
    }
	//printf("Résultat final : %s\n", result);
    return result;  // Retourne le résultat final
}


int check_dollard(char *str)
{
	int i = 0;
	int count = 0;
	while(str[i])
	{
		if(str[i] == '$')
			count++;
		i++;
	}
	return(count);
}
void	ft_echo(char **argv, t_data *data)//cf parsing
{
	int		i;
	bool	new_line;
	char	*output;

	i = 1;
	new_line = true;
	(void)fd;
	// if (fd < 1)
	// 	fd = 1;
	while (argv[i] && echo_n(argv[i]))
	{
		new_line = false;
		i++;
	}
	while (argv[i])
	{
	 	output = expand_variables_in_string(argv[i], data);  // Vérifier l'expansion de variable
	    if (output)
		{ 
            ft_putstr_fd(output, fd);
			free(output);
		}
        if (argv[i + 1])// Affiche un espace entre les arguments
            ft_putstr_fd(" ", fd);
        i++;
	}
    if (new_line)
       ft_putstr_fd("\n", fd);
}
//echo sans options -> ajoute un saut de ligne par defaut
//echo -n -> supprime le saut de ligne
//echo -nnnnn -> marche comme -n
 
	// Affiche un espace si l option -n est activee
	//if (new_line)
	//	ft_putstr_fd(" ",1);
	// Affiche un saut de ligne si l'option -n n'est pas activée
