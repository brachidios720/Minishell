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

typedef struct s_env
{
	char            *content;//stock 1 chaine de car
    struct s_env    *next;
}	t_env;

typedef struct s_cmd
{
	char            *str;//stock 1 chaine de car
    int             num; // token 
    char            *option; // option cmd 
    struct s_cmd    *next;
}	t_cmd;

typedef struct s_data
{
    t_env *copy_env;
    char *path;
    char *pwd;
    char *old_pwd;
    char *line;
    char **matrice;
    char **cut_matrice;
    int  pipe;
    struct t_cmd *cmd;
    
} t_data;

// init

void    init_data(t_data *data);
void    ft_check_line(char **av, char **envp, t_data *data, t_cmd **cmd, t_env **env);

//init_lst
t_env	*ft_env_new(t_env, char **envp, int i);
t_env	*init_env(char **envp);

// parsing 

t_cmd	*ft_lsttnew(t_data *data, int i);
void    ft_lstclearr(t_cmd **cmd);
void	ft_lst_addbackk(t_cmd **stack, t_cmd *node);
void    ft_cut_cont(char *str, t_data *data);
int     count_pipe(char *str);
void	ft_do_all(char *str, t_cmd **cmd, t_data *data, t_cmd *new_node);

// utils 
int		ft_strcmp(char *s1, char *s2);
void	print_minishell(void);
void    ft_handler(int a);
void    ft_handlequit(int b);
char    *ft_strncpy(char *s1, char *s2, int n);

// utils_2

char	**ft_strdup_tab(char **env);
int     ft_strcmp(char *s1, char *s2);
void    print_minishell(void);
void    ft_change_env(t_data *data, char *name, char *new_name);
char    *search_in_env(t_data *data, char *name);
char    *ft_strcpy(char *s1 , char *s2);
char    *ft_tab(char **av);
int     ft_lstsizee(t_cmd *cmd);

// token

void    ft_check_bultins(char *line, t_data *data, t_env **env);
int     ft_pwd(void);
void    ft_env(t_env **env);
void    ft_cd(t_data *data);
//echo.c
bool	echo_n(char *argv);
void	ft_echo(char **argv);
//export.c
void    export_with_nothing(t_env *env);
void    export_with_variable(t_env **env, char *new_var);
void    ft_export(t_env **env, char **args);

//unset.c
void	check_env(char *var_to_delete, char **env);
bool	delete_var(char *argv, char **env);
//int		ft_unset(char **argv, char **env);
// free
void	ft_free_tab(char **av);
void    ft_free(char *str, t_cmd **cmd);
//read_line.c
// pipe

# endif