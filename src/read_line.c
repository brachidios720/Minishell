/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pag <pag@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:17:57 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/11/13 14:14:54 by pag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//lecture de la ligne et appel des autres fonctions
void ft_check_line(t_data *data, t_cmd **cmd, t_env **env)
{
	t_cmd *new_node;
	data->last_exit_status = g_signal;
	char *line;

	*cmd = malloc(sizeof(t_cmd));
	new_node = NULL;
	//gérer la lecture de la ligne (bloque les interruptions comme Ctrl+C ou réinitialise les handlers).
	change_signal(0);
	line = readline(CYAN"Minishell> "RESET); 
	if(line[0] == '\0')
	{
		free(line);
		ft_check_line(data, cmd, env);
	}
	else if (line == NULL || ft_strncmp(line, "exit" , ft_strlen("exit")) == 0)
		return(free(line));
	else
	{
		add_history(line);
		data->line = line;
		init_data(data);
		ft_do_all(line, cmd, data, new_node);
		if(ft_check_option(data) == 1)
    	{
      		ft_free(line, cmd);
      		ft_check_line(data, cmd, env);
   		}
		else
		{
			data->last_exit_status = g_signal;
			//change_signal(2);  // Configuration pour here-document
			//change_signal(1);  // Configuration pour l'exécution de commande
			process_commands(data, env, cmd);
			ft_free(line, cmd);
			g_signal = 0;
			ft_check_line(data, cmd, env);
		}
	}
}

void detect_input_redirection(t_cmd *cmd, t_data *data, int *i, int *j)
{
	if (data->line[*i + 1] == '<')
	{
		cmd->redir_type[*j] = HEREDOC;
		*j += 1;
		// if (!ft_extract_delimiter(cmd, data))
		// 	return ((void)ft_printf("Erreur : impossible d'extraire le délimiteur\n"));
		*i += 1;
	}
	else
	{
		cmd->redir_type[*j] = INPUT_FILE;
		*j += 1;
	}
}

void detect_output_redirection(t_cmd *cmd, t_data *data, int *i, int *j)
{
	if (data->line[*i + 1] == '>')
	{
		cmd->redir_type[*j] = APPEND;
		*j += 1;
		*i += 1;
	}
	else
	{
		cmd->redir_type[*j] = OUTPUT_FILE;
		*j += 1;
	}
}

void detect_redirection(t_cmd *cmd, t_data *data)
{
	int			i;
	int			j;

	j = 0;
	while (j < 30)
		cmd->redir_type[j++] = -1;
	i = 0;
	j = 0;
    while (data->line[i])
    {
        if (data->line[i] == '<')
		{
			detect_input_redirection(cmd, data, &i, &j);
			i += 1;
			while (ft_isspace(data->line[i]))
				i += 1;
			if (data->line[i] != '<')
				stock_filename(cmd, &data->line[i], j);
		}
		else if (data->line[i] == '>')
		{
			detect_output_redirection(cmd, data, &i, &j);
			i += 1;
			while (ft_isspace(data->line[i]))
				i += 1;
			if (data->line[i] != '>')
				stock_filename(cmd, &data->line[i], j);
		}
		i++;
    }
}