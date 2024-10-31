#include "../../include/minishell.h"

// Fonction pour lire du stdin jusqu'à un mot spécifique pour le heredoc
bool read_in_stdin(t_data *data, int fd, char *word)
{
    (void)data;
    char *line;
    while (1)
	{
        // Demande à l'utilisateur d'entrer une ligne
        line = readline("> ");
        if (!line) // Gestion de la fin de l'entrée
            return (false);       
        // Comparaison de la ligne avec le mot de fin
        if (strcmp(line, word) == 0) {
            free(line);
            break;
        }
        // Écrit la ligne dans le fichier `fd`
        write(fd, line, strlen(line));
        write(fd, "\n", 1); // Ajoute un saut de ligne après chaque entrée
        free(line);
    }
    return (true);
}
// Fonction de gestion du heredoc en créant un fichier temporaire
int here_doc(t_data *data, char *word) 
{
    int fd;
    char *tmp_file = "/tmp/heredoc_tmp.txt"; // Fichier temporaire pour le heredoc
    // Ouvre un fichier temporaire en écriture
    fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        perror("Error opening heredoc temporary file");
        return (-1);
    }
    // Lecture du stdin et écriture dans le fichier temporaire
    if (!read_in_stdin(data, fd, word)) {
        close(fd);
        return (-1);
    }
    close(fd);
    // Réouvre le fichier en lecture pour le heredoc
    return (open(tmp_file, O_RDONLY));
}
