/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarico <almarico@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:58:25 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/11/09 21:07:38 by almarico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
gére les erreurs d’arguments ou de terminaison du programme.
*/
void	ft_exit(int i)
{
	if (i == 1)
		printf("args error\n");
	exit(0);
}

/*
 Parcourt s1 et s2 tant que les caractères sont identiques,
 retourne la différence entre les 2 caractères non identiques rencontrés.
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned int )s1[i] - (unsigned int)s2[i]);
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
	while (env[len])
		len++;
	new_tab = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_tab[i] = ft_strdup(env[i]);
		if (!new_tab[i])
		{
			free(new_tab);
			return (NULL);
		}
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

/*
Parcourt s2 et copie chaque caractère dans s1, ajoutant \0 à la fin
*/
char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0 ;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

/*
Copie caractère par caractère jusqu'à atteindre n caractères ou la fin de s1.
*/
char	*ft_strncpy(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] && i < n)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
/*
La variable i est utilisée pour parcourir chaque élément
de la liste et compter le nombre de nœuds.
*/

int	ft_llstsize(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}

int ft_is_in_quote(char *str, int i) 
{
    int count = 0;
    int ind = 0;
    while (ind < i) {
        if (str[ind] == '\'')
            count++;
        ind++;
    }
    return (count % 2 == 1);
}

int ft_is_in_doublequote(char *str, int i) 
{
    int count = 0;
    int ind = 0;
    while (ind < i) {
        if (str[ind] == '\"')
            count++;
        ind++;
    }
    return (count % 2 == 1);
}

char *ft_strdupsizee(const char *s, int size) 
{
    int i = 0;
    char *stock;

    stock = (char *)malloc(sizeof(char) * (size + 1));
    if (!stock)
        return (NULL);
    while (i < size) {
        stock[i] = s[i];
        i++;
    }
    stock[size] = '\0';
    return (stock);
}

int ft_nbredemott(char const *s, char c) 
{
    int i = 0;
    int nbrmot = 0;

    while (s[i] != '\0')
	{
        while (s[i] == c && s[i] != '\0')
            i++;
        if (s[i] != c && s[i] != '\0')
            nbrmot++;
        while (s[i] != '\0' && (s[i] != c || (s[i] == c && \
		(ft_is_in_quote((char *)s, i) || ft_is_in_doublequote((char *)s, i)))))
            i++;
    }
    return (nbrmot);
}

char **ft_splitt(char const *s, char c) 
{
    char **new;
    int nbrmot = ft_nbredemott(s, c);
    int compteur = 0;
    int size;
    int i = 0;

    new = malloc(sizeof(char *) * (nbrmot + 1));
    if (!new)
        return (NULL);
    while (compteur < nbrmot)
	{
        size = 0;
        while (s[i] == c) 
            i++;
        int start = i;
        while (s[i] && (s[i] != c || (s[i] == c && \
		(ft_is_in_quote((char *)s, i) || ft_is_in_doublequote((char *)s, i))))) 
		{
            i++;
            size++;
        }
        new[compteur] = ft_strdupsizee(s + start, size);
        compteur++;
    }
    new[compteur] = NULL;
    return (new);
}


void	is_a_quote(char c, int *state)
{
	if (c == '\'' && *state == 0)
		*state = 1;
	else if (c == '\'' && *state == 1)
		*state = 0;
	if (c == '\"' && *state == 0)
		*state = 2;
	else if (c == '\"' && *state == 2)
		*state = 0;
}

void	shift_str(char *str, int length)
{
	int	i;

	i = 0;
	while (str[i + length])
	{
		str[i] = str[i + length];
		i++;
	}
	str[i] = '\0';
}

void	trim_quotes(char **option)
{
	int	i;
	int	j;
	int	state;
	
	state = 0;
	i = 0;
	while (option[i])
	{
		j = 0;
		while (option[i][j])
		{
			is_a_quote(option[i][j], &state);
			if ((option[i][j] == '\"' && state != 1)
				|| (option[i][j] == '\'' && state != 2))
			{
				shift_str((option[i] + j), 1);
				j--;
			}
			if (j < (int)ft_strlen(option[i]))
				j++;
		}
		i++;
	}
}

char *cut_tab_dollard(char *str)
{
	int i = 0;
	int len = 0;
	int start = 0;
	char *dest = NULL;
	if(check_dollard(str))
	{
		while(str[i])
		{
			if(str[i] == '$')
			{
				i++;
				start = i;
				while(ft_isalpha(str[i]) == 1)
					i++;
				len = (i - start) + 1;
				dest = malloc(sizeof(char) * len); 
				ft_strncpy(str, dest, len);
			}
			i++;
		}
		return(dest);
	}
	else
		return(str);
}

void	ft_sign(void)
{
	signal(SIGINT, ft_handler_sig);
	signal(SIGINT, ft_handler_sig_cmd);
	signal(SIGINT, ft_handler_sig_hd);
    //signal(SIGQUIT, ft_handlequit);
}

