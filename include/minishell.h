/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <spagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:12:37 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/11/09 15:37:18 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //perror
# include <string.h> //sizeof
# include <unistd.h> //dup2 close
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h> //wexitstatus
# include <fcntl.h> //pour les constantes  O_WRONLY, O_CREAT, O_TRUNC, O_APPEND 
# include <stdlib.h>
# include <signal.h> //strcut sigaction
# include <termios.h>
# include <limits.h> //path_max
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

#define NO_REDIR 0        				// Aucun type de redirection
#define INPUT_FILE 1      				// Redirection d'entrée depuis un fichier (<)
#define HEREDOC 2         				// Redirection d'entrée via heredoc (<<)
#define OUTPUT_FILE 3     				// Redirection de sortie vers un fichier (>)
#define APPEND 4          				// Redirection de sortie en mode append (ajout) (>>)
#define READ_WRITE_EXEC 0777
#define MODE_HEREDOC 0644

extern int	g_signal;		//variable globale pour gestion des signaux

typedef struct s_cmd
{
	char	*str;	  // stock 1 chaine de car (ex : ls)
	char	*delimiter; //identfier pour le heredoc
	char	*filename; //nom du fichier 
	char	*file_tmp; //fichier temporaire
	int		num;	  // numero de token
	char	*option; // option cmd (ex-l)
	char	**matrice;
	char	**incmd;
	char	**input_files; //liste des chemins de fichiers pour la redirection d entree
	char	**output_files; //liste des chemins de fichiers pour la redirection de sortie
	int		*input_redir; // fichier pour la redirection d'entree <
	int		*output_redir;  // fichier pour la redirection de sortie >
	int		input_redir_type; // stock le type de redirection d'entree 
	int		output_redir_type;  // stock le type de redirection de sortie
	int		input_fd; //utilise pour stocker le descripteur de fichier associe a la redirection d entree
	int		output_fd; //utilisee pour stocker le descripteur de fichier associe a la redirection de sortie
	int		append; // ajout a la fin >> -> 1 sinon 0
	struct s_cmd *next;
} t_cmd;

typedef struct s_env
{
	char 			*content; // stock 1 chaine de car
	struct s_env	*next;
} t_env;
typedef struct s_data // donnees principales
{
	t_env	*copy_env;
	char	*path;
	char	*pwd;
	char	**old_pwd;
	char	*line;
	char	**matrice;
	char	*mat;
	char	**cut_matrice;
	bool	rien;
	int		nb_cmd;
	int		pipe;			  // int pour creation de pipeline
	int		last_exit_status; // int pour stocker le dernier code de retour cf echo $
	struct t_cmd *cmd;

} t_data;

//SRC
//-----------------------------------------------------------------------
//->BUILTINS
//	builtins.c
void	exec_builtin(t_cmd *cmd, t_env **env, t_data *data);
void	exec_external(t_cmd *cmd, t_env **env);
void	execute_command_or_builtin(t_cmd **cmd, t_env **env, t_data *data);
void	process_commands(t_data *data, t_env **env, t_cmd **cmd);
//  cd.c
char	*ft_get_env_value(char *name, t_env **env);
void	ft_change_env(t_env **env, char *name, char *new_value);
int		ft_change_directory(char *target_dir);
void	ft_update_env(t_env **env, char *old_pwd, char *new_pwd);
char	*ft_get_target_dir(char *target_dir, t_env **env);
void	ft_cd(t_env **env, char **target_dir);
void	init_pwd(t_env **env);

//	echo.c
bool	echo_n(char *argv);
char	*ft_itoa_m(int n);
char	*expand_variable(char *arg, t_data *data);
void	ft_echo(char **argv, t_data *data);

//	env.c
void	ft_env(t_env **env);

// export.c
void	export_with_nothing(t_env *env);
void	export_with_variable(t_env **env, char *new_var);
void	ft_export(t_env **env, char **args);

//ft_pwd.c
int    ft_pwd(void);

// unset.c
void	unset_with_variable(t_env **env, char *my_var);
int		ft_unset(t_env **env, char **args);

//	utils_builtins.c
int		is_builtin(char *cmd);


// EXEC
//---------------------------------------------------------------------------
//	exec.c
void 	exec_cmd(t_data *data, t_cmd **cmd, t_env **env);
// path.c
char	*find_command_path(char *cmd);

//INIT
//--------------------------------------------------------------------
// init_lst
void	ft_lstadd_back_list(t_env **env, t_env *n);
t_env	*ft_env_new(char **envp, int i);
t_env	*init_env(char **envp);

//init
void    init_data(t_data *data);

// parsing
//------------------------------------------------------------------
//->ft_utils_cmd.c
void	ft_lst_addbackk(t_cmd **stack, t_cmd *node);
int		ft_lstsizee(t_cmd *cmd);
void	ft_lstclearr(t_cmd **cmd);
void	ft_free(char *str, t_cmd **cmd);

//->option.c
int		ft_check_option(t_data *data);
char	*ft_check_dash(char *str);

//->parsing1.c
t_cmd	*ft_lsttnew(t_data *data, int i);
void	ft_do_all(char *str, t_cmd **cmd, t_data *data, t_cmd *new_node);

//->parsing2.c
int		ft_check_pipe(char *str);

//->utils_parsing_line
int			ft_isspace(char c);
const char	*get_filename_start(t_cmd *cmd, t_data *data, int redir_type);
const char	*stock_filename(t_cmd *cmd, const char *start, int redir_type);
char		*ft_extract_delimiter(t_cmd *cmd, t_data *data);

//->utils_parsing.c
int		count_pipe(char *str);
void	ft_cut_cont(char *str, t_data *data);
int		ft_check_one_quote(char *str);

// redirection
//-----------------------------------------------------------------
//->heredoc.c
int		ft_heredoc(t_cmd *cmd, t_data *data);
bool	read_in_stdin(t_data *data, int fd, t_cmd *cmd);
int		ft_handle_heredoc(t_cmd *cmd, t_data *data);
//->utils_heredoc.c
void	configure_heredoc_signals(struct sigaction *old_int, struct sigaction *old_quit);
void	read_input_with_heredoc(int tmp_fd, t_cmd *cmd);
//->inoutput.c
int		handle_single_input_redir(t_cmd *cmd, t_data *data);
int		handle_redir_input(t_cmd *cmd, t_data *data);
int		handle_single_output_redir(t_cmd *cmd, int index);
int		handle_redir_output(t_cmd *cmd);
//utils_redir.c
int		count_nb_redir_input(t_cmd *cmd);
void	read_input_with_heredoc(int tmp_fd, t_cmd *cmd);
int		count_nb_redir_output(t_cmd *cmd);
// signals
//---------------------------------------------------------------------------
//parse_signal.c
void	ft_handler_sig(int signal);
void	ft_handlequit(int b);
void	ft_handler_sig_cmd(int signal);
void	ft_handler_sig_hd(int signal);
void	change_signal(int pos);
//STEPH
//steph.c
void	ft_pipe_first_cmd(int pipe_fd[2], t_cmd *cmd, t_data *data);
void	ft_pipe_last_cmd(int pipe_fd[2], t_cmd *cmd, t_data *data);
void	ft_pipe_middle_cmd(int prev_fd, int pipe_fd[2], t_cmd *cmd);
void	exec_pipe_chain(t_data *data, t_cmd **cmd, t_env **env);

// free
void	ft_free_tab(char **av);

//minishell
void	print_minishell(void);

// read_line.c
void	ft_check_line(char **av, char **envp, t_data *data, t_cmd **cmd, t_env **env);
void	detect_input_redirection(t_cmd *cmd, t_data *data);
void	detect_output_redirection(t_cmd *cmd, t_data *data);

// utils_env
char	**env_list_to_array(t_env **env_list);

// utils
void	ft_exit(int i);
int		ft_strcmp(const char *s1, const char *s2);
char	**ft_strdup_tab(char **env);
char	*ft_strcpy(char *s1, char *s2);
char	*ft_strncpy(char *s1, char *s2, int n);
int		ft_llstsize(t_cmd *cmd);

#endif