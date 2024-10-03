/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:53:41 by spagliar          #+#    #+#             */
/*   Updated: 2024/09/09 15:53:43 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *find_command_path(char *cmd)
{
    char *path;
    char **paths;
    char *full_path;
    int i;

    path = getenv("PATH");
    paths = ft_split(path, ':');  // Divise le PATH en répertoires
    i = 0;  

    while (paths[i])
    {
        full_path = ft_strjoin(paths[i], "/");  // Ajoute un '/' après le répertoire
        full_path = ft_strjoin(full_path, cmd);  // Concatène avec la commande

        // Vérifie si la commande est accessible dans ce chemin
        if (access(full_path, X_OK) == 0)
        {
            return full_path;  // Retourne le chemin complet si la commande est trouvée
        }
        i++;
    }

    return NULL;  // Retourne NULL si la commande n'est pas trouvée
}

//apl execve pour executer les commandes externes
void execve_cmd(t_data *data, t_cmd *cmd)
{
    (void)*data;
    char *cmd_path = find_command_path(cmd->str);  // Recherche le chemin de la commande

    if (!cmd_path)
    {
        printf("Commande non trouvée : %s\n", cmd->str);
        return;
    }
    char *argv[] = {cmd_path, cmd->option, NULL}; //tab contien les argus de la commande
    char **envp = NULL; //init envp a NULL pour les besoins de execve on fait simple

    if (execve(cmd_path, argv, envp)==-1) //execute la commande externe
    {              //ls  -la   NULL
        perror("Erreur execve");  // Affiche l'erreur
        exit(EXIT_FAILURE);  // Termine le processus enfant en cas d'échec
    }

    free(cmd_path);  // Libère la mémoire allouée pour le chemin de la commande
}

//gere la creation du processus enfant av fork et exec la comm avec execve ds le processus enfant si ok

bool exec_cmd (t_data *data, t_cmd *cmd)
{
    pid_t pid;//stock le pid cree par fork -> permet de savoir si le processus cour est enf ou par

    pid = fork(); //creation d un nveau processus -> proc enfant recoit pid enfant proc enfant recoit 0
    if (pid < 0)
    {
        printf ("error fork");
        return (false);
    }
    else if (pid == 0) //on est ds processus enfant
    {
        execve_cmd(data, cmd);//on execute la commande ds l enfant
    }
    else //on est ds processus parent donc pid positif
    {
        waitpid(pid, NULL, 0); //on attend que l exec du processus enfant se termine av de continuer son propre flux
    }
    return (true); //cmd executer avec succes
}


//execution des commandes externes
//gere la logique, verifie les commandes et prepare les pipes
bool exec (t_data *data, t_cmd **cmd)
{
    t_cmd *tmp; //ptr accede la liste de cmd et parcourt chaque cmd a executer
    int pip[2]; //tab pour descripteur de pipe / relie deu xprocessus ->ecrire [0] lire [1] 

    tmp = *cmd; //init tmp a la premiere commande a executer

    if (tmp && tmp->str) //si commande a executer
    {
        if (data->pipe)//si cmd utilise un pipe pour communiquer -> active la fction pipe
        {
            if (pipe(pip) == -1)//si utilise un pipe -> creation du pipe avec la fonction
            {
                return (false);//si == -1 -> false
            }
        }
        exec_cmd(data, tmp);//apl de la fonction pour executer la cmd
                                 //pip en parametre pour gerer la comm entre processus   
    }
    return (true);//exuec reussi
}

/*  ls : Lister les fichiers dans un répertoire.
    cat : Afficher le contenu d’un fichier.
    grep : Rechercher une chaîne dans un fichier.
    wc : Compter les lignes, mots et caractères d’un fichier.
    date : Afficher la date et l’heure actuelles.
*/

