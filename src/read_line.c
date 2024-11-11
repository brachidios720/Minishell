/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pag <pag@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:17:57 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/11/11 11:27:18 by pag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//lecture de la ligne et appel des autres fonctions
void ft_check_line(char **av, char **envp, t_data *data, t_cmd **cmd, t_env **env)
{
	t_cmd *new_node;
	signal(SIGINT, ft_handler_sig);
	signal(SIGINT, ft_handler_sig_cmd);
	signal(SIGINT, ft_handler_sig_hd);
    signal(SIGQUIT, ft_handlequit);
	char *line;
	
	new_node = NULL;
	//gérer la lecture de la ligne (bloque les interruptions comme Ctrl+C ou réinitialise les handlers).
	change_signal(0);
	line = readline(CYAN"Minishell> "RESET); 
	if(line == NULL || ft_strncmp(line, "exit" , ft_strlen("exit")) == 0)
		return(free(line));
	add_history(line);
	data->line = line;
	init_data(data);
	ft_do_all(line, cmd, data, new_node);
	if(ft_check_option(data) == 1)
	{
		ft_free(line, cmd);
		ft_check_line(av, envp, data, cmd, env);
	}
	else
	{
		change_signal(2);  // Configuration pour here-document
		
		change_signal(1);  // Configuration pour l'exécution de commande
		process_commands(data, env, cmd);
		
		ft_free(line, cmd);
		ft_check_line(av, envp, data, cmd, env);
	}
}

void detect_input_redirection(t_cmd *cmd, t_data *data)
{
    int i;
	int nb_redir;

	i = 0;
	nb_redir = count_nb_redir_input(cmd);
	
    // Allocation de mémoire pour les redirections d'entrée
    cmd->input_redir_type = malloc(sizeof(int) * nb_redir);
    if (!cmd->input_redir_type)
        return ((void)ft_printf("Erreur : allocation échouée pour input_redir_type\n"));

    // Initialiser le tableau à nb_redir
    while (i < nb_redir)
        cmd->input_redir_type[i++] = nb_redir;
		printf ("je suis dans detect input redr : %d\n", i);
    // Réinitialisation de l'indice pour l'analyse
    i = 0;
    while (data->line[i])
    {
        if (data->line[i] == '<')
        {
            if (data->line[i + 1] == '<')
            {
                cmd->input_redir_type[i] = HEREDOC;
                if (!ft_extract_delimiter(cmd, data))
                    return ((void)ft_printf("Erreur : impossible d'extraire le délimiteur\n"));
                i++;
            }
            else
            {
                cmd->input_redir_type[i] = INPUT_FILE;
                const char *filename_start = get_filename_start(cmd, data, INPUT_FILE);
                if (filename_start && !stock_filename(cmd, filename_start, INPUT_FILE))
                    return ((void)ft_printf("Erreur : impossible de stocker le fichier d'entrée\n"));
            }
        }
        i++;
    }
}

/*
// Détecte et gère les redirections et le heredoc dans la ligne de commande
void detect_input_redirection(t_cmd *cmd, t_data *data)
{
	const char *filename_start;
	int	i;
	cmd->input_redir_type = NO_REDIR;


	i = 0;
	while (data->line[i])
	{
		if (data->line[i] == '<')
		{
			if (data->line[i + 1] == '<')
			{
				cmd->input_redir_type = HEREDOC;
				//cmd->delimiter = ft_extract_delimiter(cmd, data);// Extrait et stocke le délimiteur du heredoc
				if (!ft_extract_delimiter(cmd, data))//extrait le delimiteur
					return ((void)ft_printf("on extrait pas le delimiteur cf detect_redir\n "));	
				i++;
			}
			else 
			{
				cmd->input_redir_type = INPUT_FILE;
				filename_start = get_filename_start(cmd, data, INPUT_FILE);  // Trouve le début du nom de fichier
				if (filename_start && !stock_filename(cmd, filename_start, INPUT_FILE)) // Extrait et stocke le nom de fichier
						return ((void)ft_printf("Erreur: impossible de stocker le fichier d'entrée -> < \n"));
			}
		}
		i++;
	}
}
*/
void detect_output_redirection(t_cmd *cmd, t_data *data)
{
	const char	*filename_start;
	int	i;
	cmd->output_redir_type = NO_REDIR;
	
	i = 0;
	
	while (data->line[i])
	{
		printf("ok 1 %c\n", data->line[i]);
		if (data->line[i] == '>')
		{
			printf("ok 2\n");
			if (data->line[i + 1] == '>')
			{
				printf("ok 3\n");
				cmd->output_redir_type = APPEND;
				filename_start = get_filename_start(cmd, data, APPEND);  // Trouve le début du nom de fichier
				if (filename_start)
				{
					if (!stock_filename(cmd, filename_start, APPEND))  // Extrait et stocke le nom de fichier
					{
						ft_printf("Erreur: impossible de stocker le fichier en mode append -> >>\n");
						return;
					}
				}
			}
			else
			{
				printf("ok output1\n");
				cmd->output_redir_type = OUTPUT_FILE;
				filename_start = get_filename_start(cmd, data, OUTPUT_FILE);  // Trouve le début du nom de fichier
				if (filename_start)
				{
					printf("ok output2\n");
					if (!stock_filename(cmd, filename_start, OUTPUT_FILE))  // Extrait et stocke le nom de fichier
					{
						ft_printf("Erreur: impossible de stocker le fichier de sortie -> >\n");
						return;
					}
				}
			}
		}
		i++;
	}	
}
	// if (ft_strnstr(data->line, "<<",ft_strlen(data->line)))
	// {
	// 	cmd->input_redir_type = HEREDOC;
	// 	//cmd->delimiter = ft_extract_delimiter(cmd, data);// Extrait et stocke le délimiteur du heredoc
	// 	if (!ft_extract_delimiter(cmd, data))//extrait le delimiteur
	// 	{
	// 		ft_printf("on extrait pas le delimiteur cf detect_redir\n ");
	// 		return;
	// 	}
	// }
	// if (ft_strnstr(data->line, "<", ft_strlen(data->line)))
	// {
	// 	cmd->input_redir_type = INPUT_FILE;
	// 	filename_start = get_filename_start(cmd, data, INPUT_FILE);  // Trouve le début du nom de fichier
	// 	if (filename_start)
	// 	{
	// 		if (!stock_filename(cmd, filename_start, INPUT_FILE))  // Extrait et stocke le nom de fichier
	// 		{
	// 			ft_printf("Erreur: impossible de stocker le fichier d'entrée -> < \n");
	// 			return;
	// 		}
	// 	}
	// }
