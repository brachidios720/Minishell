/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pag <pag@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:17:57 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/11/03 20:37:16 by pag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Détecte et gère les redirections et le heredoc dans la ligne de commande
void detect_redirections_and_heredoc(t_cmd *cmd, t_data *data)
{
    const char *filename_start;

    // Détecte le heredoc ("<<")
    if (ft_strnstr(data->line, "<<",ft_strlen(data->line)))
    {
        cmd->input_redir_type = HEREDOC;
        cmd->delimiter = extract_delimiter(cmd, data);// Extrait et stocke le délimiteur du heredoc
        if (!cmd->delimiter)
        {
            fprintf(stderr, "Erreur: impossible d'extraire le délimiteur du heredoc\n");
            return;
        }
    }
    // Détecte la redirection d'entrée ("<")
    if (ft_strnstr(data->line, "<", ft_strlen(data->line)))
    {
        cmd->input_redir_type = INPUT_FILE;
        filename_start = get_filename_start(cmd, data, INPUT_FILE);  // Trouve le début du nom de fichier
        if (filename_start)
        {
            if (!stock_filename(cmd, filename_start, INPUT_FILE))  // Extrait et stocke le nom de fichier
            {
                fprintf(stderr, "Erreur: impossible de stocker le fichier d'entrée\n");
                return;
            }
        }
    }
    // Détecte la redirection de sortie en mode append (">>")
    if (ft_strnstr(data->line, ">>", ft_strlen(data->line)))
    {
        cmd->output_redir_type = APPEND;
        filename_start = get_filename_start(cmd, data, APPEND);  // Trouve le début du nom de fichier
        if (filename_start)
        {
            if (!stock_filename(cmd, filename_start, APPEND))  // Extrait et stocke le nom de fichier
            {
                fprintf(stderr, "Erreur: impossible de stocker le fichier en mode append\n");
                return;
            }
        }
    }
    // Détecte la redirection de sortie simple (">")
    else if (ft_strnstr(data->line, ">", ft_strlen(data->line)))
    {
        cmd->output_redir_type = OUTPUT_FILE;
        filename_start = get_filename_start(cmd, data, OUTPUT_FILE);  // Trouve le début du nom de fichier
        if (filename_start)
        {
            if (!stock_filename(cmd, filename_start, OUTPUT_FILE))  // Extrait et stocke le nom de fichier
            {
                fprintf(stderr, "Erreur: impossible de stocker le fichier de sortie\n");
                return;
            }
        }
    }
}

//lecture de la ligne et appel des autres fonctions
void ft_check_line(char **av, char **envp, t_data *data, t_cmd **cmd, t_env **env)
{
    t_cmd *new_node = NULL;

    signal(SIGINT, ft_handler);
    signal(SIGQUIT, ft_handlequit);
    char *line = readline(CYAN"Minishell> "RESET);
    if(line == NULL || ft_strncmp(line, "exit" , ft_strlen("exit")) == 0)
        return(free(line));
    add_history(line);
    data->line = line;
    // Initialisation des données
    init_data(data);
    // Détection des redirections et heredocs
    detect_redirections_and_heredoc(*cmd, data);
    // Processus de parsing et exécution
    ft_do_all(line, cmd, data, new_node);
    // Si des options spécifiques sont détectée
    if(ft_check_option(data) == 1)
    {
        ft_free(line, cmd);
        ft_check_line(av, envp, data, cmd, env);
    }
    else
    {
        process_commands(data, env, cmd);
        ft_free(line, cmd);
        ft_check_line(av, envp, data, cmd, env);
    }
}
