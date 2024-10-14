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

void parse_command(char **matrice, t_cmd **cmd)
{
    int i;

    i = 0;
    //Alloue de la mem pour 1 nvlle commande à partir de la première partie de la ligne
    *cmd = malloc(sizeof(t_cmd));
    if (*cmd == NULL)
    {
        perror("Erreur d'allocation de mémoire pour cmd");
        return;
    }
    //copie le 1er elemt de matrice = la commande dans str de la structure t_cmd ex:ls
    (*cmd)->str = ft_strdup(matrice[0]);
    //si 2 elemts = copie sinon = null ex -l ou rien
    (*cmd)->option = matrice[1] ? ft_strdup(matrice[1]) : NULL;  // Option (ex: -l)
    //init ptr next a NULL = fin
    (*cmd)->next = NULL;

    //boucle pour analyse des redirections
    while (matrice[i])
    {
        //si fichier d 'entree = le fichier d apres -> ds infile
        if (!ft_strcmp(matrice[i], "<"))
            (*cmd)->infile = matrice[i+1];
        //sinon fichier de sortie = fichier d apres -> ds outfile 
        else if (!ft_strcmp(matrice[i], ">"))
        {
            (*cmd)->outfile = matrice[i+1];
            //mise a jour = fichier ecrase
            (*cmd)->append = 0;
        }
        //sinon si fichier de sortie avec ajout au fichier existant -> ds outfile + 1
        else if(!ft_strcmp(matrice[i], ">>"))
        {
            (*cmd)->outfile = matrice[i+1];
            (*cmd)->append = 1;
        }
        //heredoc
        else if (strcmp(matrice[i], "<<") == 0)
        {
            ft_handle_heredoc(matrice[i+1]);
            i++;
        }
        i++;
    }
}

//lecture de la ligne et appel des autres fonctions
void ft_check_line(char **av, char **envp, t_data *data, t_cmd **cmd, t_env **env)
{
    char *line = readline("Minishell> ");
    add_history(line);
    data->line = line;

    // Si aucune commande n'a été saisie ou si l'utilisateur tape "exit", on quitte
    if (line == NULL || ft_strcmp(line, "exit") == 0)
    {
        free(line);
        return;
    }

    // Séparer la ligne de commande en fonction des espaces
    data->matrice = ft_split(line, ' ');  // Découpe la ligne de commande
    if (data->matrice[0] == NULL)  // Si la ligne est vide
    {
        free(line);
        return;
    }
    //analyse la commandes et les redirections
    parse_command(data->matrice, cmd);
    // Exécuter la commande
    exec(data, cmd);
    // Vérifier si la commande est un built-in
    ft_check_builtins(line, data, env);
    // Libérer la ligne et les commandes après l'exécution
    ft_free(line, cmd);
    // Relancer pour attendre la commande suivante
    ft_check_line(av, envp, data, cmd, env);
}
