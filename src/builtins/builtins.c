/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:35:56 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/17 18:24:40 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void exec_builtin(t_cmd *cmd, t_env **env, t_data *data)
{
    pid_t pid = fork();
    
    if (pid == 0) // Processus enfant
    {
        // Exécute le builtin dans l'enfant
        if (ft_strcmp(cmd->matrice[0], "cd") == 0)
            ft_cd(env, cmd->matrice);
        else if (ft_strcmp(cmd->matrice[0], "echo") == 0)
            ft_echo(cmd->matrice, data);
        else if (ft_strcmp(cmd->matrice[0], "env") == 0)
            ft_env(env);
        else if (ft_strcmp(cmd->matrice[0], "pwd") == 0)
            ft_pwd();
        else if (ft_strcmp(cmd->matrice[0], "export") == 0)
            ft_export(env, cmd->matrice);
        else if (ft_strcmp(cmd->matrice[0], "unset") == 0)
            ft_unset(env, cmd->matrice);
          // Quitter après l'exécution du builtin
    }
    else if (pid > 0)  // Processus parent
    {
        waitpid(pid, NULL, 0);  // Attendre que le processus enfant se termine
    }
    else
    {
        perror("Erreur de fork");
        exit(EXIT_FAILURE);
    }
}

void exec_external(t_cmd *cmd, t_env **env)
{
    char *cmd_path;
    char **envp;
    envp = env_list_to_array(env); // Convertir env en tableau pour execve
    cmd_path = find_command_path(cmd->matrice[0]);  // Trouver le chemin complet de la commande

    if (cmd_path == NULL) {
        perror("Commande non trouvée");
        printf("b\n");
        exit(EXIT_FAILURE);
    }
    if (execve(cmd_path, cmd->matrice, envp) == -1) {
        perror("Erreur execve");
        free(cmd_path);
        free(envp);
        printf("z\n");
        exit(EXIT_FAILURE);
    }
}

void execute_command_or_builtin(t_cmd *cmd, t_env **env, t_data *data)
{    // Redirections et exécution des builtins ou commandes externes
    handle_redirections(cmd);

    printf("%s\n", cmd->str);
    if (is_builtin(cmd->str) == 1)  // Si c'est un builtin
    {
        printf("s\n");
        exec_builtin(cmd, env, data);  // Terminer l'enfant après avoir exécuté le builtin
    }
    else
    {
        printf("sd\n");
        exec_external(cmd, env);  // Exécuter une commande externe via execve
    }
}


void process_commands(t_data *data, t_env **env, t_cmd *cmd)
{
    int i = 0;
    // Vérifier s'il y a des pipes dans les commandes
    if (count_pipe(data->line))
    {
        // Appeler la fonction qui gère l'exécution des commandes pipées
        ft_handle_pipe_with_heredoc(cmd, cmd->matrice[i], data, env);
    }
    else
    {
        // Si pas de pipe, exécuter la commande (builtin ou externe)
        execute_command_or_builtin(cmd, env, data);
    }
}



// void      ft_check_builtins(char *line, t_data *data, t_env **env, t_cmd **cmd)
// {
//     t_cmd *tmp;
//     tmp = *cmd;
//     if(line == NULL || line[0] == '\0' || tmp == NULL || tmp->str == NULL)
//         return;
//     handle_redir_in_out(tmp);
//     if(ft_strncmp(tmp->str, "env", ft_strlen("env")) == 0)
//         ft_env(env);
//     else if(ft_strncmp(tmp->str, "pwd", ft_strlen("pwd")) == 0)
//         ft_pwd();
//     else if(ft_strncmp(tmp->str, "echo", ft_strlen("echo")) == 0)
//         ft_echo(tmp->matrice, data);
//     else if(ft_strncmp(tmp->str, "cd", ft_strlen("cd")) == 0)
//        ft_cd(env, tmp->matrice);
//     else if(ft_strncmp(tmp->str, "export", ft_strlen("export")) == 0)
//         ft_export(env, tmp->matrice);
//     else if(ft_strncmp(tmp->str, "unset", ft_strlen("unset")) == 0)
//         ft_unset(env, tmp->matrice);
//     else
//     {
//         if(tmp->next)
//         {
//             exec_pipe_chain(data, *cmd);
//         }
//         else
//             exec_cmd(data, tmp);
//     }
//     free(data->matrice);
// }