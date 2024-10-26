/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:23:20 by spagliar          #+#    #+#             */
/*   Updated: 2024/10/26 14:23:22 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef struct s_cmd
{
    int infile;
} t_cmd;

void	ft_pipe_first_cmd(int pipe_fd[2], t_cmd *cmd)
{
    if (pipe(pipe_fd) == -1)
    {
        perror("Erreur de création du pipe");
        exit(EXIT_FAILURE);
    }
    printf("Pipe créé avec succès\n");

    if (cmd->infile != STDIN_FILENO)
    {
        if (dup2(cmd->infile, STDIN_FILENO) == -1)
        {
            perror("Erreur de redirection de l'entrée");
            exit(EXIT_FAILURE);
        }
        printf("Redirection de l'entrée standard réussie\n");
    }
    if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
    {
        perror("Erreur de redirection de la sortie");
        exit(EXIT_FAILURE);
    }
    printf("Redirection de la sortie standard réussie\n");

    close(pipe_fd[0]);
    close(pipe_fd[1]);
}

int main(void)
{
    int pipe_fd[2];
    t_cmd cmd;
    char buffer[1024];
    ssize_t bytes_read;

    cmd.infile = open("input.txt", O_RDONLY);
    if (cmd.infile == -1)
    {
        perror("Erreur d'ouverture du fichier d'entrée");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("Erreur de fork");
        close(cmd.infile);
        return EXIT_FAILURE;
    }
    else if (pid == 0)
    {
        ft_pipe_first_cmd(pipe_fd, &cmd);
        execlp("echo", "echo","contenu de test", NULL);
        perror("Erreur lors de l'exécution de echo");
        exit(EXIT_FAILURE);
    }
    else
    {
        close(pipe_fd[1]);

        while ((bytes_read = read(pipe_fd[0], buffer, sizeof(buffer) - 1)) > 0)
        {
            buffer[bytes_read] = '\0';
            printf("%s", buffer);
        }

        waitpid(pid, NULL, 0);
        close(pipe_fd[0]);
        printf("\nProcessus enfant terminé\n");
    }

    close(cmd.infile);
    return EXIT_SUCCESS;
}
