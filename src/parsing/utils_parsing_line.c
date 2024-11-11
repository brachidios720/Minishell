#include "../../include/minishell.h"

//identifier si caractere espace ou speciale
int ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' ||
		c == '\v' || c == '\f' || c == '\r');
}

//donne la position du debut du nom de fichier apres un symbole de redirection
// const char *get_filename_start(t_cmd *cmd, t_data *data, int redir_type)
// {
//     const char *symbol;
//     const char *pos;
//     
//     // Détermine le symbole de redirection en fonction du type
//     if (redir_type == INPUT_FILE) 
//         symbol = "<";
//     else if (redir_type == OUTPUT_FILE)
//         symbol = ">";
//     else if (redir_type == APPEND)
//         symbol = ">>";
//     else 
//         return NULL;  // Type de redirection non pris en charge
//
//     // Trouve la position du symbole dans la ligne de commande
//     pos = ft_strnstr(data->line, symbol, ft_strlen(data->line));
//     if (!pos)
//         return NULL;
//     pos += ft_strlen(symbol);  // Se déplace après le symbole
//     while (*pos && ft_isspace(*pos))  // Ignore les espaces après le symbole
//         pos++;
//     return (pos);  // Retourne la position du début du nom de fichier
// }

// Fonction pour extraire et stocker le nom de fichier dans la structure t_cmd
void	stock_filename(t_cmd *cmd, const char *start, int j)
{
	const char	*pos;
	size_t		len;
	char		*filename;

	pos	= start;
	while (*pos && !ft_isspace(*pos))
		pos++;
	len = pos - start;
	filename = malloc(len + 1);
	if (!filename)
		return ;
	ft_strncpy((char *)start, filename, len);
	filename[len] = '\0';
	cmd->payload[j] = ft_strdup(filename);
	free(filename);
}

// const char *stock_filename(t_cmd *cmd, const char *start, int redir_type)
// {
//     // Trouve la fin du nom de fichier
//     const char *pos;
//     size_t len;
//     char *filename;
//     
//     pos = start;
//     while (*pos && !ft_isspace(*pos))
//         pos++;
//
//     // Copie le nom du fichier dans une nouvelle chaîne
//     len = pos - start;
//     filename = malloc(len + 1);
//     if (!filename)
//         return NULL;
//
//     ft_strncpy((char *)start, filename, len);
//     filename[len] = '\0';
//
//     // Stocke le nom du fichier dans cmd selon le type de redirection
//     if (redir_type == INPUT_FILE) 
//     {
//         cmd->input_files = malloc(sizeof(char *) * 2);
//         if (!cmd->input_files) 
//         {
//             free(filename);
//             return NULL;
//         }
//         cmd->input_files[0] = filename;
//         cmd->input_files[1] = NULL;
//     }
//     else if (redir_type == OUTPUT_FILE || redir_type == APPEND) 
//     {
//         cmd->output_files = malloc(sizeof(char *) * 2);
//         if (!cmd->output_files)
//         {
//             free(filename);
//             return NULL;
//         }
//         cmd->output_files[0] = filename;
//         cmd->output_files[1] = NULL;
//         if (redir_type == APPEND)
//             cmd->append = 1;
//     }
//     return (filename);
// }

// Fonction pour extraire le délimiteur du heredoc
// char *ft_extract_delimiter(t_cmd *cmd, t_data *data)
// {
//     char *pos;
//     char *start;
//     size_t len;
//     
//     // Trouve la position de "<<" dans la ligne de cmd
//     pos = ft_strnstr(data->line, "<<", ft_strlen(data->line));
//     // Si heredoc n'est pas trouvé, retourne NULL
//     if (!pos)
//         return NULL;
//     // Se déplace après "<<"
//     pos += 2;
//     // Ignore les espaces apres <<
//     while (*pos && ft_isspace(*pos))
//         pos++;
//     // determmine le début et la fin du délimiteur
//     start = pos;
//
//     // Trouve la fin du mot (délimiteur) en cherchant le prochain espace ou la fin de la ligne
//     while (*pos && !ft_isspace(*pos))
//         pos++;
//
//     // Copie le délimiteur dans une nouvelle chaîne
//     len = pos - start;
//     cmd->delimiter = malloc(len + 1);
//     if (!cmd->delimiter)
//         return NULL;
//
//     //ft_strncpy(cmd->delimiter,(char *)start, len);
//     cmd->delimiter = ft_substr(start, 0, len);
//     //cmd->delimiter[len] = '\0';
//
//     return (cmd->delimiter);
// }
