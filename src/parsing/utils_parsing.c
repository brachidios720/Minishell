#include "../../include/minishell.h"

int count_pipe(char *str)
{
    int i;
    int y;
    
    i = 0;
    y = 0;
    while(str[i])
    {
        if(str[i] == '|')
            y++;
        i++;
    }
    return(y);
}

void    ft_cut_cont(char *str, t_data *data)
{
    int i = 0;
    data->pipe = count_pipe(str);
    data->cut_matrice = ft_split(str, '|');
    while(data->cut_matrice[i])
    {
        data->cut_matrice[i] = ft_strtrim(data->cut_matrice[i], " ");
        i++;
    }
}
void ft_handle_heredoc(char *delimiter)
{
    int pipefd[2];
    char *line;
    if (pipe(pipefd) == -1) 
    {
        perror("pipe");
        return;
    }
    // Lire les lignes de l'utilisateur jusqu'à rencontrer le délimiteur
    while (1)
    {
        line = readline("> ");  // Afficher un prompt pour la saisie
        if (!line || strcmp(line, delimiter) == 0) {
            free(line);
            break;
        }
        // Écrire la ligne dans le pipe
        write(pipefd[1], line, strlen(line));
        write(pipefd[1], "\n", 1);  // Ajouter un saut de ligne après chaque entrée
        free(line);
    }
    // Fermer le côté écriture du pipe
    close(pipefd[1]);
    // Rediriger l'entrée standard (stdin) vers le côté lecture du pipe
    dup2(pipefd[0], STDIN_FILENO);
    // Fermer le côté lecture du pipe après la redirection
    close(pipefd[0]);
}