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
# include <readline/history.h>
# include "../LIBFT/libft.h"
# include "../LIBFT/printff/ft_printf.h"
# include "../LIBFT/get_next_linee/get_next_line.h"
# include "../LIBFT/get_next_linee/get_next_line_bonus.h"

typedef struct	s_env//gestion de env
{
	void			*content;//ptr pour stocker des chaines de car->var d'env ex: "VAR=value"
	struct s_env	*next;//ptr ver 2nd element suivant de la liste ex: "HOME=/home/user"

}		t_env;

typedef struct s_cmd//gestion des pipes
{
	int				num; // token pour identifier la commande
	char			*str;//stock le nom de la commande (ls, echo etc)
	char			*option;//option cmd (-l, -n etc) 
	struct s_cmd	*next;//ptr vers la prochaine commande (ls | grep foo)
}	t_cmd;

typedef struct s_data //donnees principales
{
	char			**copy_env;//copy des var sous forme de tab de chaine de car
	char			*path;
	char			*pwd;
	char			*old_pwd;
	char			*line;
	char			**matrice;
	char			**cut_matrice;
	int				pipe;
	struct s_env	*env;//liste chainee des var d'environnement
	struct t_cmd	*cmd;//ptr vers la 1ere commande de la liste chainee

}	t_data;

// init
void	init_data(t_data *data);
void	ft_check_line(char **av, char **env, t_data *data);

// parsing 
t_cmd	*ft_lsttnew(void *content);
int		ft_check_pipe(char c);
char	*ft_cut_cont(char *str);
int		count_pipe(char *str);

// utils 
void	ft_exit(int i);
int		ft_strcmp(char *s1, char *s2);
void	print_minishell(void);
char	**ft_strdup_tab(char **env);
char	*ft_strcpy(char *s1, char *s2);
char	*ft_strncpy(char *s1, char *s2, int n);
char	**lst_to_tab(t_env *env);//export->utils env
int		len_list(t_env *env);//export
void	sort_array(char **arr, int len);//export
void	ft_handler(int a);//readline
void	ft_handlequit(int b);//ctrl
void	ft_change_env(t_data *data, char *name, char *new_name);//cd
char	*search_in_env(t_data *data, char *name);//init
char	*ft_tab(char **av);//init

// token
void	ft_check_bultins(char *line, t_data *data);
int		ft_pwd(void);
void	ft_env(char **str);
void	ft_cd(t_data *data);
bool	echo_n(char *argv);//echo
void	ft_echo(char **argv);//echo
int		exist(char *argv, char **copy_env);
bool	export_no_args(t_env *env);//export

// free
void	ft_free_tab(char **av);

#endif
