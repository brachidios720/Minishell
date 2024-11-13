#include "../../include/minishell.h"

 void    init_data(t_data *data)
{
     //data->path = search_in_env(data, "PATH=");
    data->pwd = getcwd(NULL, PATH_MAX);
    data->old_pwd = data->pwd;
    data->mat = NULL;
    data->rien = TRUE;

}

void    init_cmd(t_cmd *cmd)
{
    int i;

    cmd->input_fd = -1;
    cmd->output_fd = -1;
    cmd->pipe_fd[0] = -1; //desc fichier pr lire
    cmd->pipe_fd[1] = -1; //desc fichier pr ecrire
    
    i = 0;
    while (i < 30)
    {
        cmd->redir_type[i] = -1;
        cmd->payload[i] = NULL;
        i++;
    }
    
    cmd->matrice = NULL;
    cmd->option = NULL;
    cmd->delimiter = NULL;
    cmd->str = NULL; 
    cmd->next = NULL;
}