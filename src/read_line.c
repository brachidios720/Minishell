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

void ft_handle_pipe_with_heredoc(t_cmd *cmd, char *delimiter)
{
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return;
    }
    // Premier fork pour la première commande (ex: ls)
    pid1 = fork();
    if (pid1 == 0)
    {
        dup2(pipefd[1], STDOUT_FILENO);  // Rediriger la sortie de cmd1 vers le pipe
        close(pipefd[0]);
        close(pipefd[1]);
        execve_cmd(NULL, cmd);  // Exécuter la première commande (par exemple, `ls`)
        perror("execve_cmd");  // Si execve échoue
        exit(EXIT_FAILURE);
    }
    if (cmd -> next)
    {
        // Deuxième fork pour la deuxième commande (ex: cat) avec heredoc
        pid2 = fork();
        if (pid2 == 0)
        {
            close(pipefd[1]);  // Fermer le côté écriture du pipe
            dup2(pipefd[0], STDIN_FILENO);  // Rediriger l'entrée standard de cmd2 depuis le pipe

            // Injecter le heredoc dans le pipe
            char *line;
            while (1)
            {
                line = readline(" > ");
                if (!line || strcmp(line, delimiter) == 0)
                {
                    free(line);
                    break;
                }
                write(STDIN_FILENO, line, strlen(line));  // Écrire dans stdin
                write(STDIN_FILENO, "\n", 1);  // Ajouter un saut de ligne
                free(line);
            }
            close(pipefd[0]);  // Fermer le pipe une fois le heredoc injecté
            execve_cmd(NULL, cmd->next);  // Exécuter la deuxième commande (par exemple, `cat`)
            perror("execve_cmd");  // Si execve échoue
            exit(EXIT_FAILURE);
        }
    }
    // Parent - Fermer les deux côtés du pipe après le fork
    close(pipefd[0]);
    close(pipefd[1]);
    // Attendre les deux processus enfants
    waitpid(pid1, NULL, 0);
    if (cmd->next)
        waitpid(pid2, NULL, 0);
}

void parse_command(char **matrice, t_cmd **cmd)
{
    t_cmd *tmp;
    int i;

    i = 0;
    tmp = *cmd;
    //boucle pour analyse des redirections
    while (matrice[i])
    {
        //si fichier d 'entree = le fichier d apres -> ds infile
        if (!ft_strcmp(matrice[i], "<"))
        {
            tmp->infile = matrice[i+1];
            i++; //passe a l element suivant apres le fichier d entree
        //sinon fichier de sortie = fichier d apres -> ds outfile 
        }
        else if (!ft_strcmp(matrice[i], ">"))
        {
            tmp->outfile = matrice[i+1];
            //mise a jour = fichier ecrase
            tmp->append = 0;
            i++; //passe au suivant
        }
        //sinon si fichier de sortie avec ajout au fichier existant -> ds outfile + 1
        else if(!ft_strcmp(matrice[i], ">>"))
        {
            tmp->outfile = matrice[i+1];
            tmp->append = 1;
            i++;
        }
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
    if(line == NULL || ft_strncmp(line, "exit" , ft_strlen("exit")) == 0)
        return(free(line));
    add_history(line);
    data->line = line;
    init_data(data);
    ft_do_all(line, cmd, data, new_node);
    parse_command(matrice, cmd);
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
