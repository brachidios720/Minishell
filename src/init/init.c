#include "../../include/minishell.h"

 void    init_data(t_data *data)
{
     //data->path = search_in_env(data, "PATH=");
    data->pwd = getcwd(NULL, PATH_MAX);
    data->old_pwd = data->pwd;
    data->mat = NULL;
    data->rien = TRUE;
}
