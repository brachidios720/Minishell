/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:12:37 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/11 16:05:16 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef minishell_h
#define minishell_h

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <limits.h>
#include <curses.h>
#include <term.h>
#include <stdbool.h>
#include <readline/readline.h>
#include "../LIBFT/libft.h"
#include "../LIBFT/printff/ft_printf.h"
#include "../LIBFT/get_next_linee/get_next_line.h"
#include "../LIBFT/get_next_linee/get_next_line_bonus.h"


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
    struct t_chain *chain;
    
} t_data;

// init

void    init_data(t_data *data);

// parsing 


// utils 

void    ft_exit(int i);
int     ft_strcmp(char *s1, char *s2);
void    ft_check_line(char **av, char **env);
void    print_minishell(void);

// token


// bultins

void    ft_check_bultins(char *line, char **env);
int     ft_pwd(void);
void    ft_env(char **str);
void    ft_echo(char **argv);
void    ft_cd(char *path);


// pipe




// free

void    ft_free_tab(char **av);

#endif