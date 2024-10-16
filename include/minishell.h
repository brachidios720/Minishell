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
# include <sys/types.h>
# include <sys/wait.h> //wexitstatus
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

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

typedef struct s_env
{
	char            *content;//stock 1 chaine de car
    struct s_env    *next;
}	t_env;
typedef struct s_cmd
{
	char            *str;//stock 1 chaine de car (ex : ls)
    int             num; // numero de token 
    char            *option; // option cmd (ex-l) 
    char            *infile; //fichier pour la redirection d'entree <
    char            *outfile; //fichier pour la redirection de sortie > ou >> ajout
    int             append; //ajout a la fin >> -> 1 sinon 0
    char            **matrice;
    struct s_cmd    *next;
}	t_cmd;

typedef struct s_data //donnees principales
{
    t_env *copy_env;
    char *path;
    char *pwd;
    char *old_pwd;
    char *line;
    char **matrice;
    char *mat;
    bool    real; 
    char **cut_matrice;
    int  pipe;//int pour creation de pipeline
    int last_exit_status; //int pour stocker le dernier code de retour cf echo $ 
    struct t_cmd *cmd;
    
} t_data;

// init
void    init_data(t_data *data);
void    ft_check_line(char **av, char **envp, t_data *data, t_cmd **cmd, t_env **env);

//init_lst
void	ft_lstadd_back_list(t_env **env, t_env *n);
t_env	*ft_env_new(char **envp, int i);
t_env	*init_env(char **envp);

// parsing 
t_cmd	*ft_lsttnew(t_data *data, int i);
void    ft_lstclearr(t_cmd **cmd);
void	ft_lst_addbackk(t_cmd **stack, t_cmd *node);
void    ft_cut_cont(char *str, t_data *data);
void    ft_handle_heredoc(char *delimiter);
int     count_pipe(char *str);
void	ft_do_all(char *str, t_cmd **cmd, t_data *data, t_cmd *new_node);
char    *ft_check_dash(char *str);
int     ft_check_option(t_data *data);
int     ft_check_one_quote(char *str);
int     ft_check_pipe(char *str);

// utils 
void	ft_exit(int i);
int		ft_strcmp(char *s1, char *s2);
void	print_minishell(void);
char	**ft_strdup_tab(char **env);
char    *ft_strcpy(char *s1 , char *s2);
char	*ft_strncpy(char *s1, char *s2, int n);
void    ft_change_cd(t_env **env, char *new_dir);
void    ft_change_env(t_env **env, char *name, char *new_value);
char    *ft_get_env_value(char *name, t_env **env);
char    *ft_tab(char **av);
int     ft_lstsizee(t_cmd *cmd);
int     ft_change_directory(char *target_dir);
void    ft_update_env(t_env **env, char *old_pwd, char *new_pwd);
char    *ft_get_target_dir(char *target_dir, t_env **env);
void    init_pwd(t_env **env);
//utils_env
//char	*ft_strchr_env(const char *s, int c);
//int   ft_strncmp_env(const char *s1, const char *s2, size_t n);

// token
void    ft_check_builtins(char *line, t_data *data, t_env **env, t_cmd **cmd);
int     ft_pwd(void);
void    ft_env(t_env **env);
void    ft_cd(t_env **env, char **target_dir);

//exec.c
char    *find_command_path(char *cmd);
void    handle_redir(t_cmd *cmd);
void    execve_cmd(t_data *data, t_cmd *cmd);
bool    exec_cmd (t_data *data, t_cmd *cmd);
bool    exec (t_data *data, t_cmd **cmd);

//ctrl.c
void    ft_handler(int a);
void    ft_handlequit(int b);
//echo.c
bool	echo_n(char *argv);
char    *expand_variable(char *arg, t_data *data);
char	*ft_itoa_m(int n);
void	ft_echo(char **argv , t_data *data);
//export.c
void    export_with_nothing(t_env *env);
void    export_with_variable(t_env **env, char *new_var);
void    ft_export(t_env **env, char **args);
//unset.c
void    unset_with_variable(t_env **env, char *my_var);
int     ft_unset(t_env **env, char **args);
// free
void	ft_free_tab(char **av);
void    ft_free(char *str, t_cmd **cmd);
//read_line.c
void    parse_command(char **matrice, t_cmd **cmd);
// pipe

#endif