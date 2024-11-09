/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <spagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:51:08 by spagliar          #+#    #+#             */
/*   Updated: 2024/11/09 16:13:21 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

int g_signal;

//gestion du ctrl+c
void    ft_handler_sig(int signal)
{
    if (signal == SIGINT)
	{
    	write(1, "^C\n", 3);
    	rl_on_new_line();
    	rl_replace_line("", 0);
    	rl_redisplay();
		g_signal = SIGINT;
	}
}

void    ft_handlequit(int b)
{
    (void)b;
}

//gestion de signal pour un cmd
void	ft_handler_sig_cmd(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		g_signal = SIGINT;
	}
	if (signal == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
}

//pour un heredoc
void	ft_handler_sig_hd(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		g_signal = SIGINT;
	}
	if (signal == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
}

//fonction global qui permet de choisir les actions suivant l'argument
void	change_signal(int pos)
{
	struct sigaction	sig_int;//ctrl+c
	struct sigaction	sig_quit;//ctrl+

	//ft_bzero(&sig_int, sizeof(sig_int));//reinit ou init les valeurs des structures a 0
	//ft_bzero(&sig_quit, sizeof(sig_quit));
	sig_int.sa_flags = SA_RESTART; //drapeau -> appel systemes interrompus = signal redemarre automatiquement
	sig_quit.sa_flags = SA_RESTART;
	if (pos == 0)
	{
		sig_int.sa_handler = &ft_handler_sig;
		sig_quit.sa_handler = SIG_IGN;
	}
	else if (pos == 1)
	{
		sig_int.sa_handler = &ft_handler_sig_cmd;
		sig_quit.sa_handler = &ft_handler_sig_cmd;
	}
	else
	{
		sig_int.sa_handler = &ft_handler_sig_hd;
		sig_quit.sa_handler = &ft_handler_sig_hd;
		sig_int.sa_flags = 0;
	}
	sigaction(SIGINT, &sig_int, NULL);
	sigaction(SIGQUIT, &sig_quit, NULL);
}