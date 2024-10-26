/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:17:57 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/18 14:19:31 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void parse_redirection(char **matrice, t_cmd *cmd)
{
    int i;

    i = 0;
    //boucle pour analyse des redirections
    while (matrice[i])
    {
        //si fichier d 'entree = le fichier d apres -> ds infile
        if (!ft_strcmp(matrice[i], "<"))
        {cmd->infile_path = matrice[i+1];
            i++; //passe a l element suivant apres le fichier d entree
        //sinon fichier de sortie = fichier d apres -> ds outfile 
        }
        else if (!ft_strcmp(matrice[i], ">"))
        {
            cmd->outfile_path = matrice[i+1];
            //mise a jour = fichier ecrase
            cmd->append = 0;
            i++; //passe au suivant
        }
        //sinon si fichier de sortie avec ajout au fichier existant -> ds outfile + 1
        else if(!ft_strcmp(matrice[i], ">>"))
        {
            cmd->outfile_path = matrice[i+1];
            cmd->append = 1;
            i++;
        }
        i++;
    }
}

//lecture de la ligne et appel des autres fonctions
void ft_check_line(char **av, char **envp, t_data *data, t_cmd **cmd, t_env **env)
{
    t_cmd *new_node = NULL;

    signal(SIGINT, ft_handler);
    signal(SIGQUIT, ft_handlequit);
    char *line = readline(CYAN"Minishell> "RESET);
    add_history(line);
    data->line = line;
    if(line == NULL || ft_strcmp(line, "exit") == 0)
        return(free(line));
    init_data(data);
    ft_do_all(line, cmd, data, new_node);
    if(ft_check_option(data) == 1)
    {
        ft_free(line, cmd);
        ft_check_line(av, envp, data, cmd, env);
    }
    else
    {
        ft_check_builtins(line, data, env, cmd);
        ft_free(line, cmd);
        ft_check_line(av, envp, data, cmd, env);
    }
}
        /*
        else if (strcmp(matrice[i], "<<") == 0)
        {
            ft_handle_heredoc(matrice[i+1]); //apl le heredoc
            i++; //passe au delimiteur
        }
        else if (strcmp(matrice[i], "|") == 0 && strcmp(matrice[i+2], "<<") == 0)
        {
  
        else if (strcmp(matrice[i], "<<") == 0)
        {
            ft_handle_heredoc(matrice[i+1]); //apl le heredoc
            i++; //passe au delimiteur
        }
        else if (strcmp(matrice[i], "|") == 0 && strcmp(matrice[i+2], "<<") == 0)
        {
            // Création d'une nouvelle commande pour la suite après le pipe
            tmp->next = malloc(sizeof(t_cmd));  // Allouer la prochaine commande
            tmp = tmp->next;  // Avancer vers la prochaine commande
            tmp->str = matrice[i+1];  // Mettre la commande suivante (cat, par exemple)
            
            //gestion du pipe avec heredoc et i+3 = delimiteur
            ft_handle_pipe_with_heredoc(*cmd, matrice[i+3]);
            i = i+3 ; //on saute le pipe et le heredoc
        }
        else
        {
            tmp->str = matrice[i];
        }
                  // Création d'une nouvelle commande pour la suite après le pipe
            tmp->next = malloc(sizeof(t_cmd));  // Allouer la prochaine commande
            tmp = tmp->next;  // Avancer vers la prochaine commande
            tmp->str = matrice[i+1];  // Mettre la commande suivante (cat, par exemple)
            
            //gestion du pipe avec heredoc et i+3 = delimiteur
            ft_handle_pipe_with_heredoc(*cmd, matrice[i+3]);
            i = i+3 ; //on saute le pipe et le heredoc
        }
        else
        {
            tmp->str = matrice[i];
        }
        */