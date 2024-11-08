#include "../../include/minishell.h"

// Fonction pour lire du stdin jusqu'à un mot spécifique pour le heredoc
bool read_in_stdin(t_data *data, int fd, t_cmd *cmd)
{
    (void)  data;
    char    *line;

    while (1)
	{
        // Demande à l'utilisateur d'entrer une ligne
        line = readline("> ");
        if (!line) // Gestion de la fin de l'entrée
            return (false);
        // Comparaison de la ligne avec le mot de fin
        if (strcmp(line, cmd->delimiter) == 0)
        {
            free(line);
            break;
        }
        // Écrit la ligne dans le fichier `fd`
        write (fd, line, strlen(line));
        write (fd, "\n", 1); // Ajoute un saut de ligne après chaque entrée
        free (line);
    }
    return (true);
}
int ft_handle_heredoc(t_cmd *cmd, t_data *data)
{
    (void)data;
    int pipefd[2];
    char *line;
    
    if (!cmd->delimiter) 
    {
        ft_printf("no délimiteur spécifié pour le heredoc cf heredoc.c.\n");
        return (-1);
    }
    //creation du pipe
    if (pipe(pipefd) == -1) 
    {
        perror("erreur lors de la creation du pipe");
        return (-1);
    }
    //lecture des lignes jusqu au delimiteur
    while (1) 
    {
        line = readline("> "); // Prompt utilisateur
        if (!line || strcmp(line, cmd->delimiter) == 0)
        { // Délimiteur trouvé
            free(line);
            break;
        }
        write(pipefd[1], line, strlen(line)); // Écrire dans le pipe
        write(pipefd[1], "\n", 1);
        free(line);
    }
    close(pipefd[1]); // Ferme le côté écriture
    cmd->matrice[1] = NULL;
    cmd->input_fd = pipefd[0]; // Stocke le descripteur de lecture
    return (0);
}

/*
// Fonction de gestion du heredoc en créant un fichier temporaire
int ft_heredoc(t_data *data, t_cmd *cmd)
{
    (void)data;
    int tmp_fd;
    //verif exraire le delimiteur pour le heredoc
    if (!ft_extract_delimiter(cmd, data))
    {
        ft_printf("pas besoin d'extraire le délimiteur du heredoc.\n");
        return -1;
    }
    // Ouvrir un fichier temporaire pour le here-document
    tmp_fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (tmp_fd == -1)
    {
        perror("Erreur lors de l'ouverture du fichier temporaire");
        return -1;
    }

    read_input_with_heredoc(tmp_fd, cmd);
    close(tmp_fd);
    // Utilisez le contenu du fichier temporaire comme nécessaire
    return (0);
}*/

