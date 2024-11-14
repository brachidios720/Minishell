/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pag <pag@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:14:10 by spagliar          #+#    #+#             */
/*   Updated: 2024/11/13 19:59:33 by pag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int	handle_single_input_redir(t_cmd *cmd, t_data *data, int i)
{
	int	fd;

	fd = -1;
	if (cmd->redir_type[i] == INPUT_FILE)
	{
		fd = open(cmd->payload[i], O_RDONLY);
		dprintf(2, "in fd; %d\n", fd);
	}
	else if (cmd->redir_type[i] == HEREDOC)
	{
		cmd->delimiter = ft_strdup(cmd->payload[i]);
		fd = ft_heredoc(cmd, data);	
	}
	//cmd->input_fd = fd;
	return (fd);
}

int	handle_single_output_redir(t_cmd *cmd, int index)
{
	int	fd;

	fd = -1;
	if (cmd->redir_type[index] == OUTPUT_FILE)
		fd = open(cmd->payload[index], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (cmd->redir_type[index] == APPEND)
		fd = open(cmd->payload[index], O_WRONLY | O_CREAT | O_APPEND, 0777);
	return (fd);
}


void handle_redirection(t_cmd *cmd, t_data *data)
{
    int i = 0;
	int y = 0;
	while(cmd->redir_type[y])
	{
		printf("cmd_redirtype = %d\n", y);
		y++;
	}
    while (cmd->redir_type[i] != -1)
    {
		//printf("Fffffffffffffff\n");
        if (cmd->redir_type[i] == INPUT_FILE || cmd->redir_type[i] == HEREDOC)
        {
            if (cmd->input_fd != -1 && cmd->input_fd != STDIN_FILENO)
                close(cmd->input_fd);
            
            cmd->input_fd = handle_single_input_redir(cmd, data, i);
            if (cmd->input_fd < 0)
            {
                perror("input fd error");
                return;
            }
            dprintf(2, "handle_redirection input fd == %d\n", cmd->input_fd);
        }
        else if (cmd->redir_type[i] == OUTPUT_FILE || cmd->redir_type[i] == APPEND)
        {
            if (cmd->output_fd != -1 && cmd->output_fd != STDOUT_FILENO)
                close(cmd->output_fd);

            cmd->output_fd = handle_single_output_redir(cmd, i);
            if (cmd->output_fd < 0)
            {
                perror("output fd error");
                return;
            }
            dprintf(2, "handle_redirection output fd == %d\n", cmd->output_fd);
        }
        i++;
    }

    // Valeurs par défaut pour les redirections
    if (cmd->input_fd == -1)
        cmd->input_fd = dup(STDIN_FILENO);
    if (cmd->output_fd == -1)
        cmd->output_fd = dup(STDOUT_FILENO);
}

// void	handle_redirection(t_cmd *cmd, t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd->redir_type[i] != -1)
// 	{
// 		if (cmd->redir_type[i] == INPUT_FILE || cmd->redir_type[i] == HEREDOC)
// 		{
// 			cmd->input_fd = handle_single_input_redir(cmd, data, i);
// 			if (cmd->input_fd < 0)
// 			{
// 				perror("input fd error");
// 			}
// 			dprintf(2, "handle_redirectoin input fd == %d\n", cmd->input_fd);
// 		}
// 		else if (cmd->redir_type[i] == OUTPUT_FILE
// 			|| cmd->redir_type[i] == APPEND)
// 		{
// 			//if (cmd->output_fd != -1 && cmd->output_fd != STDOUT_FILENO)
// 			//	close(cmd->output_fd);
// 			cmd->output_fd = handle_single_output_redir(cmd, i);
// 		}
// 		i++;
// 	}
// 	if (cmd->input_fd == -1)
// 	{
// 		cmd->input_fd = dup(STDIN_FILENO);
// 	}
// 	if (cmd->output_fd == -1)
// 	{
// 		cmd->output_fd = dup(STDOUT_FILENO);
// 	}
// }
