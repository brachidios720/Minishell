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

typedef struct s_cmd
{
	char            *str;//stock 1 chaine de car (ex : ls)
    int             output; //variable pour la redirection d'entree cf pipe.c
    int             input; //variable pour la redirection de sortie cf pipe.c
    char            *infile_path; //idem pour les fichiers cf inout
    char            *outfile_path; //idem pour les fichers cf inout
    int             num; // numero de token 
    char            *option; // option cmd (ex-l) 
    int             append; //ajout a la fin >> -> 1 sinon 0
    char            **matrice;
    char            **incmd;
    struct s_cmd    *next;
}	t_cmd;

typedef struct s_env
{
	char            *content;//stock 1 chaine de car
    struct s_env    *next;
}	t_env;
typedef struct s_data //donnees principales
{
    t_env           *copy_env;
    char            *path; //chaîne de car pour stocker la valeur de la variable d'environnement
    char            **paths; //in tab de chaine pour stocker les # repertoires de PATH
    char            *full_path; //chaine qui comtient le chemin complet de la cmd
    char            *pwd;
    char            *old_pwd;
    char            *line;
    char            **matrice;
    char            *mat;
    bool            real; 
    char            **cut_matrice;
    int             pip; //pour la creation de pipe cf exec
    int             pipe_fd[2];//int pour creation de pipeline [0]lire [1]ecrire
    int             read_fd_cmd;//lecture du fd envoye 
    int             last_exit_status; //int pour stocker le dernier code de retour cf echo $ 
    int             flag;//index
    struct t_cmd    *cmd;

} t_data;

//BUILTINS
//----------------------------------------------------------------------------------
//builtins.c
void    ft_check_builtins(char *line, t_data *data, t_env **env, t_cmd **cmd);
//cd.c
char    *ft_get_env_value(char *name, t_env **env);
void    ft_change_env(t_env **env, char *name, char *new_value);
int     ft_change_directory(char *target_dir);
void    ft_update_env(t_env **env, char *old_pwd, char *new_pwd);
char    *ft_get_target_dir(char *target_dir, t_env **env);
void    ft_cd(t_env **env, char **target_dir);
void    init_pwd(t_env **env);
//echo.c
bool	echo_n(char *argv);
char    *expand_variable(char *arg, t_data *data);
char	*ft_itoa_m(int n);
void	ft_echo(char **argv , t_data *data);
//env.c
void    ft_env(t_env **env);
//export.c
void    export_with_nothing(t_env *env);
void    export_with_variable(t_env **env, char *new_var);
void    ft_export(t_env **env, char **args);
//pwd.c
int     ft_pwd(void);
//unset.c
void    unset_with_variable(t_env **env, char *my_var);
int     ft_unset(t_env **env, char **args);
//CTRL
//---------------------------------------------------------------------------------
//ctrl.c
void    ft_handler(int a);
void    ft_handlequit(int b);
//EXEC
//---------------------------------------------------------------------------------
//exec.c
char    **prepare_argv(t_cmd *cmd, char *cmd_path);
void    exec_with_env_and_redir(t_cmd *cmd, t_data *data);
void    execve_cmd(t_data *data, t_cmd *cmd);
void	exec_cmd(t_data *data, t_cmd *cmd);
bool	exec(t_data *data, t_cmd **cmd);
//inout_files.c
void	handle_redir_in_out(t_cmd *cmd);
//path.c
char	*find_command_path(t_data *data, t_cmd *cmd);
//pipe.c
void	ft_pipe_first_cmd(t_data *data, t_cmd *cmd);
void	ft_pipe_last_cmd(t_data *data, t_cmd *cmd);
void	ft_pipe_middle_cmd(t_data *data, t_cmd *cmd);
void	ft_pipe(t_data *data, t_cmd *cmd);
void	exec_pipe_chain(t_data *data, t_cmd *cmd);
//HEREDOC
//---------------------------------------------------------------------------------
//heredoc.c
void ft_exec_second_cmd_with_heredoc(t_cmd *cmd, char *delimiter, t_data *data);
void ft_exec_second_cmd_with_heredoc(t_cmd *cmd, char *delimiter, t_data *data);
void ft_handle_pipe_with_heredoc(t_cmd *cmd, char *delimiter, t_data *data);
//INIT
//-------------------------------------------------------------------------------
// init.c
void    init_data(t_data *data);
//init_lst.c
void	ft_lstadd_back_list(t_env **env, t_env *n);
t_env	*ft_env_new(char **envp, int i);
t_env	*init_env(char **envp);
// PARSING
//-------------------------------------------------------------------------------- 
//ft_utils_cmd.c
void	ft_lst_addbackk(t_cmd **stack, t_cmd *node);
int     ft_lstsizee(t_cmd *cmd);
void    ft_lstclearr(t_cmd **cmd);
void    ft_free(char *str, t_cmd **cmd);
//option.c
int     ft_check_option(t_data *data);
char    *ft_check_dash(char *str);
//parsing1.c
t_cmd	*ft_lsttnew(t_data *data, int i);
void	ft_do_all(char *str, t_cmd **cmd, t_data *data, t_cmd *new_node);
//parsing2.c
int     ft_check_pipe(char *str);
//utils_parsing.c
int     count_pipe(char *str);
void    ft_cut_cont(char *str, t_data *data);
void    ft_handle_heredoc(char *delimiter);
int     ft_check_one_quote(char *str);
//TRANSFER
//--------------------------------------------------------------------------------
char *ft_find_path(char *commande);
//free.c
void	ft_free_tab(char **av);
void    ft_free_split(char **av);
//read_line.c
void    parse_redirection(char **matrice, t_cmd *cmd);
void    ft_check_line(char **av, char **envp, t_data *data, t_cmd **cmd, t_env **env);
//utils_env
char	**env_list_to_array(t_env *env_list);
//utils.c
void	ft_exit(int i);
int		ft_strcmp(char *s1, char *s2);
void	print_minishell(void);
char	**ft_strdup_tab(char **env);
char    *ft_strcpy(char *s1 , char *s2);
char	*ft_strncpy(char *s1, char *s2, int n);

#endif