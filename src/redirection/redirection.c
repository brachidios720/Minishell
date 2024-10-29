#include "../../include/minishell.h"

// void handle_redirections(t_cmd *cmd)
// {
//     int fd;

//     // Si redirection de sortie
//     if (cmd->outfile)
//     {
//         if (cmd->append)  // Si on doit ajouter à la fin du fichier
//             fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
//         else  // Si on doit écraser le fichier
//             fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        
//         if (fd == -1)
//         {
//             perror("Erreur ouverture fichier de sortie");
//             exit(EXIT_FAILURE);
//         }
//         dup2(fd, STDOUT_FILENO);  // Rediriger la sortie standard
//         close(fd);
//     }

//     // Si redirection d'entrée
//     if (cmd->infile)
//     {
//         fd = open(cmd->infile, O_RDONLY);
//         if (fd == -1)
//         {
//             perror("Erreur ouverture fichier d'entrée");
//             exit(EXIT_FAILURE);
//         }
//         dup2(fd, STDIN_FILENO);  // Rediriger l'entrée standard
//         close(fd);
//     }
// }

// void parse_redirection(char **matrice, t_cmd *cmd) 
// {
//     int i = 0;

//     // Boucle pour analyse des redirections
//     while (matrice[i]) {
//         // Si redirection de sortie (">")
//         if (matrice[i] && ft_strcmp(matrice[i], ">") == 0 && matrice[i + 1])
//         {
//             if (cmd->outfile) 
//                 free(cmd->outfile);  // Libérer si déjà défini
//             cmd->outfile = ft_strdup(matrice[i + 1]);
//             cmd->append = 0;
//             i += 2; // Passer à l'élément suivant après le fichier de sortie
//         }
//         // Si redirection de sortie avec ajout (">>")
//         else if (matrice[i] && ft_strcmp(matrice[i], ">>") == 0 && matrice[i + 1]) 
//         {
//             if (cmd->outfile) 
//                 free(cmd->outfile);  // Libérer si déjà défini
//             cmd->outfile = ft_strdup(matrice[i + 1]);
//             cmd->append = 1;
//             i += 2;
//         }
//         // Si redirection d'entrée ("<")
//         else if (matrice[i] && ft_strcmp(matrice[i], "<") == 0 && matrice[i + 1]) 
//         {
//             if (cmd->infile) 
//                 free(cmd->infile);  // Libérer si déjà défini
//             cmd->infile = ft_strdup(matrice[i + 1]);
//             i += 2;
//         }
//         else
//             i++; // Si ce n'est pas une redirection, avancer
//     }
// }

// void ft_handle_pipe_with_heredoc(t_cmd *cmd, char *delimiter, t_data *data, t_env **env)
// {
//     int pipefd[2];
//     pid_t pid1, pid2 = 0;

//     if (pipe(pipefd) == -1)
//     {
//         perror("pipe");
//         return;
//     }
//     // Premier fork pour la première commande (ex: ls)
//     pid1 = fork();
//     if (pid1 == 0)
//     {
//         dup2(pipefd[1], STDOUT_FILENO);  // Rediriger la sortie de cmd1 vers le pipe
//         close(pipefd[0]);
//         close(pipefd[1]);
//         execute_command_or_builtin(&cmd, env, data);  // Exécuter la première commande (par exemple, `ls`)
//         //perror("execve_cmd");  // Si execve échoue
//         exit(EXIT_FAILURE);
//     }
//     if (cmd -> next)
//     {
//         // Deuxième fork pour la deuxième commande (ex: cat) avec heredoc
//         pid2 = fork();
//         if (pid2 == 0)
//         {
//             close(pipefd[1]);  // Fermer le côté écriture du pipe
//             dup2(pipefd[0], STDIN_FILENO);  // Rediriger l'entrée standard de cmd2 depuis le pipe

//             // Injecter le heredoc dans le pipe
//            if(ft_strcmp(cmd->str, "<<") == 0)
//            {
//                 char *line;
//                 while (1)
//                 {
//                     line = readline(" > ");
//                     if (!line || strcmp(line, delimiter) == 0)
//                     {
//                         free(line);
//                         break;
//                     }
//                     write(STDIN_FILENO, line, strlen(line));  // Écrire dans stdin
//                     write(STDIN_FILENO, "\n", 1);  // Ajouter un saut de ligne
//                     free(line);
//                 }
//             }
//             close(pipefd[0]);  // Fermer le pipe une fois le heredoc injecté
//             execute_command_or_builtin(&cmd->next, env, data);  // Exécuter la deuxième commande (par exemple, `cat`)
//         }

//         //perror("execve_cmd");  // Si execve échoue
//         //exit(EXIT_FAILURE);
//     }
//     // Parent - Fermer les deux côtés du pipe après le fork
//     close(pipefd[0]);
//     close(pipefd[1]);
//     // Attendre les deux processus enfants
//     waitpid(pid1, NULL, 0);
//     if (cmd->next)
//     {
//         waitpid(pid2, NULL, 0);
//     }
// }


// void execute_pipeline(t_cmd *cmd_list, t_env **env, t_data *data)
// {
//     int pipe_fds[2];
//     pid_t pid;
//     int fd_in = 0; // Entrée du prochain processus

//     printf("f\n");
//     while (cmd_list) {
//         pipe(pipe_fds); // Crée un pipe pour chaque commande

//         if ((pid = fork()) == 0) { // Processus enfant
//             dup2(fd_in, STDIN_FILENO); // Rediriger l'entrée du processus
//             if (cmd_list->next)
//                 dup2(pipe_fds[1], STDOUT_FILENO); // Si pas dernière commande, rediriger sortie vers pipe
//             close(pipe_fds[0]);
//             execute_command_or_builtin(cmd_list, env, data); // Exécute la commande (builtin ou execve)
//         }
//         else { // Processus parent
//             wait(NULL); // Attendre l'enfant
//             close(pipe_fds[1]);
//             fd_in = pipe_fds[0]; // Pour la prochaine commande
//             cmd_list = cmd_list->next;
//         }
//     }
// }


// void ft_handle_pipe_with_heredoc(t_cmd *cmd, char *delimiter, t_data *data, t_env **env)
// {
//     pid_t pid;
//     int pipfd[2];

//     while(cmd != NULL)
//     {
//         if(pipe(pipfd) == -1)
//         {
//             perror("pipe");
//             return;
//         }
//         pid = fork();
//         if(pid == 0)
//         {
//             dup2(pipefd[1], STDOUT_FILENO);  // Rediriger la sortie de cmd1 vers le pipe
//             close(pipefd[0]);
//             close(pipefd[1]);
//             execute_command_or_builtin(&cmd, env, data);
//         }

//         cmd = cmd->next; 
//     }
// }