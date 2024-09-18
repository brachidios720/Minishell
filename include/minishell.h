/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:12:37 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/17 17:00:28 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <limits.h>
# include <curses.h>
# include <term.h>
# include <stdbool.h>
# include <readline/readline.h>
# include "../LIBFT/libft.h"
# include "../LIBFT/printff/ft_printf.h"
# include "../LIBFT/get_next_linee/get_next_line.h"
# include "../LIBFT/get_next_linee/get_next_line_bonus.h"

typedef struct s_chain
{
	char	*str;//stock 1 chaine de car
}	t_chain;

typedef struct s_data
{
	char			**av;//tab de chaine ->stock les arg de argv[]
	char			**copy_env;//tab de chaine contient les var env ->copy de l'env 
	char			*path;//chaine qui contient le chemin de lexecutable d'une commade
	char			*pwd;//chaine represente -> le rep de travail actuel
	char			*old_pwd;//chaine qui stock la valeur precedente du rep de travail ->pour revenir en arriere
	struct t_chain	*chain;
}	t_data;

// structure

typedef struct s_chain
{
    char            *str;
    struct t_chain  *prev;
    struct t_chain  *next;
    
}   t_chain;

typedef struct s_data
{
    char **copy_env;
    char *path;
    char *pwd;
    char *old_pwd;
    char *line;
    char **matrice;
    struct t_chain *chain;
    
} t_data;

// init

void    init_data(t_data *data);

void    ft_check_line(char **av, char **env, t_data *data);
// parsing 

// utils 
void	ft_exit(int i);
int		ft_strcmp(char *s1, char *s2);
void	print_minishell(void);

// utils_2
char	**ft_strdup_tab(char **env);
void	sort_array(char **env, int len);
bool	check_id(char *argv);
int		search_var(char *argv, char **env);
void    ft_exit(int i);
int     ft_strcmp(char *s1, char *s2);
void    print_minishell(void);
char	**ft_strdup_tab(char **env);
void    ft_change_env(t_data *data, char *name, char *new_name);
char    *search_in_env(t_data *data, char *name);
char    *ft_strcpy(char *s1 , char *s2);
char    *ft_tab(char **av);

// token

void    ft_check_bultins(char *line, char **env, t_data *data);
int     ft_pwd(void);
void    ft_env(char **str);
void    ft_cd(t_data *data);
bool	echo_n(char *argv);
void	ft_echo(char **argv);
bool	export_no_args(char **env, int len);
int		exist(char *argv, char **copy_env);
bool	export(char *argv, char **copy_env);
int		ft_export	(char **argv, char **copy_env);
//export.c
//unset.c
void	check_env(char *var_to_delete, char **env);
bool	delete_var(char *argv, char **env);
int		ft_unset(char **argv, char **env);
// free
void	ft_free_tab(char **av);
//read_line.c
// pipe

# endif