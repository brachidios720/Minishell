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


void ft_check_line(char **av, char **envp, t_data *data, t_cmd **cmd, t_env **env)
{
    //t_cmd *new_node = NULL;
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

    // Initialiser la commande à partir de la première partie de la ligne
    *cmd = malloc(sizeof(t_cmd));
    if (*cmd == NULL)
    {
        perror("Erreur d'allocation de mémoire pour cmd");
        free(line);
        return;
    }

    (*cmd)->str = ft_strdup(data->matrice[0]);  // Commande (ex: ls)
    (*cmd)->option = data->matrice[1] ? ft_strdup(data->matrice[1]) : NULL;  // Option (ex: -l)
    (*cmd)->next = NULL;

    // Exécuter la commande
    exec(data, cmd);

    // Vérifier si la commande est un built-in
    ft_check_builtins(line, data, env);

    // Libérer la ligne et les commandes après l'exécution
    ft_free(line, cmd);

    // Relancer pour attendre la commande suivante
    ft_check_line(av, envp, data, cmd, env);
}
