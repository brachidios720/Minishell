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

//trouve le chemin de la commande
char *find_command_path(char *cmd)
{
    char *path; //stock la valeur de la var d'env PATH
    char **paths; //tab de chaines de car qui stock les rep separes par des ":" a partir de PATH
    char *full_path; //stock le chemin complet de la commande -> concatene le rep et la commande
    int i; //parcourt les repertoires dans paths

    path = getenv("PATH");
    paths = ft_split(path, ':');
    i = 0;  

    while (paths[i])
    {
        full_path = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(full_path, cmd);
        if (access(full_path, X_OK) == 0)
            return full_path;
        i++;
    }
    return NULL;
}

void handle_redir(t_cmd *cmd)
{
    // Gestion de redirections d'entree et de sortie
    if (cmd->infile)
    {
        int fd_in;
        fd_in = open(cmd->infile, O_RDONLY);
        if (fd_in < 0)
        {
            perror("Erreur ouverture fichier d'entrée");
            exit(EXIT_FAILURE);
        }
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
    }
    if (cmd->outfile)
    {
        int fd_out;
        if (cmd->append)
            fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);

        if (fd_out < 0)
        {
            perror("Erreur ouverture fichier de sortie");
            exit(EXIT_FAILURE);
        }
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
    }
}
//apl execve pour executer les commandes externes
void execve_cmd(t_data *data, t_cmd *cmd)
{
    (void)*data;
    char *cmd_path = find_command_path(cmd->str);
    if (!cmd_path)
    {
        printf("Commande non trouvée : %s\n", cmd->str);
        return;
    }
    char *argv[] = {cmd_path, cmd->option, NULL};
    char **envp = NULL;

    //gestion de redirection
    handle_redir(cmd);
    //execute la commande externe
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
    pid_t pid;
    int status; //recupere le code de retour

    pid = fork();
    if (pid < 0)
    {
        printf ("error fork");
        return (false);
    }
    else if (pid == 0)
        execve_cmd(data, cmd);
    else
    {
        waitpid(pid, &status, 0); //recupere avec l& le status du processus fils
        if (WIFEXITED(status)) //verif si fin et extrait le code retour
        {
            data->last_exit_status = WEXITSTATUS(status);//stock le code de retour
        }
    }
    return (true);
}

//execution des commandes externes
//gere la logique, verifie les commandes et prepare les pipes
bool exec (t_data *data, t_cmd **cmd)
{
    t_cmd *tmp;
    int pip[2];

    tmp = *cmd;

    if (tmp && tmp->str)
    {
        if (data->pipe)
        {
            if (pipe(pip) == -1)
                return (false);
        }
        exec_cmd(data, tmp);
    }
    return (true);//exuec reussi
}
