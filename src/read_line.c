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
    init_data(data);
    ft_do_all(line, cmd, data, new_node);
    if(ft_check_option(data) == 1)
    {
        ft_free(line, cmd);
        ft_check_line(av, envp, data, cmd, env);
    }
    else
    {
        process_commands(data, env, *cmd);
        ft_free(line, cmd);
        ft_check_line(av, envp, data, cmd, env);
    }
}

// //lecture de la ligne et appel des autres fonctions
// void ft_check_line(char **av, char **envp, t_data *data, t_cmd **cmd, t_env **env)
// {
//     char *line = readline("Minishell> ");
//     add_history(line);
//     data->line = line;

//     // Si aucune commande n'a été saisie ou si l'utilisateur tape "exit", on quitte
//     if (line == NULL || ft_strcmp(line, "exit") == 0)
//     {
//         free(line);
//         return;
//     }

//     // Séparer la ligne de commande en fonction des espaces
//     data->matrice = ft_split(line, ' ');  // Découpe la ligne de commande
//     if (data->matrice[0] == NULL)  // Si la ligne est vide
//     {
//         free(line);
//         return;
//     }
//     //analyse la commandes et les redirections
//     parse_command(data->matrice, cmd);
//     // Exécuter la commande
//     exec(data, cmd);
//     // Vérifier si la commande est un built-in
//     ft_check_builtins(line, data, env);
//     // Libérer la ligne et les commandes après l'exécution
//     ft_free(line, cmd);
//     // Relancer pour attendre la commande suivante
//     ft_check_line(av, envp, data, cmd, env);
// }


// void parse_redirection(char **matrice, t_cmd *cmd)
// {
//     int i;

//     i = 0;
//     //boucle pour analyse des redirections
//     while (matrice[i])
//     {
//         //si fichier d 'entree = le fichier d apres -> ds infile
//         if (!ft_strcmp(matrice[i], "<"))
//         {
//             cmd->infile = ft_strdup(matrice[i+1]);
//             i++; //passe a l element suivant apres le fichier d entree
//         //sinon fichier de sortie = fichier d apres -> ds outfile 
//         }
//         else if (!ft_strcmp(matrice[i], ">"))
//         {
//             cmd->outfile = ft_strdup(matrice[i+1]);
//             //mise a jour = fichier ecrase
//             cmd->append = 0;
//             i++; //passe au suivant
//         }
//         //sinon si fichier de sortie avec ajout au fichier existant -> ds outfile + 1
//         else if(!ft_strcmp(matrice[i], ">>"))
//         {
//             cmd->outfile = ft_strdup(matrice[i+1]);
//             cmd->append = 1;
//             i++;
//         }
//         // else if (strcmp(matrice[i], "<<") == 0)
//         // {
//         //     ft_handle_heredoc(matrice[i+1]); //apl le heredoc
//         //     i++; //passe au delimiteur
//         // }
//         // else if (strcmp(matrice[i], "|") == 0 && strcmp(matrice[i+2], "<<") == 0)
//         // {
//         //     // Création d'une nouvelle commande pour la suite après le pipe
//         //     tmp->next = malloc(sizeof(t_cmd));  // Allouer la prochaine commande
//         //     tmp = tmp->next;  // Avancer vers la prochaine commande
//         //     tmp->str = matrice[i+1];  // Mettre la commande suivante (cat, par exemple)
            
//         //     //gestion du pipe avec heredoc et i+3 = delimiteur
//         //     ft_handle_pipe_with_heredoc(*cmd, matrice[i+3]);
//         //     i = i+3 ; //on saute le pipe et le heredoc
//         // }
//         // else
//         // {
//         //     tmp->str = matrice[i];
//         // }
//         i++;
//     }
// }