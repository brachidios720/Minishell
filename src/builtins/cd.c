/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:07:49 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/17 18:28:33 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void    ft_cd(char *path)
// {
//     char *old_pwd = getenv("PWD");
//     char cwd[PATH_MAX];
    
//     if(path == NULL || strcmp(path, "") == 0)
//         path = getenv("HOME");
//     if(ft_strcmp(path, "-"))
//         getenv("OLD_PWD");
//         if(path == NULL)
//             return;
//     if(chdir(path) != 0)
//     {
//         printf("error\n");
//         return;
//     }
//     setenv("OLD_PWD", old_pwd, 1);
//     if(getcwd(cwd, sizeof(cwd)) != NULL)
//         setenv("PWD", cwd, 1);
//     else
//         perror(cwd);
// }


/*
void    ft_change_env(t_data *data, char *name, char *new_name)
{
    int i = 0;
    char *tmp;
    
    while(data->copy_env[i])
    {
        if(ft_strncmp(data->copy_env[i], name, ft_strlen(name)) == 0)
        {
            free(data->copy_env[i]);
            tmp = ft_strjoin(name, new_name);
            data->copy_env[i] = ft_strdup(tmp);
            free(tmp);
        }
        i++;
    }
}
void    ft_change_cd(t_data *data, char *env)
{
    char *str;

    if(chdir(env) == 0)
    {
        str = getcwd(NULL, PATH_MAX);
        ft_change_env(data, "PWD=", str);
        ft_change_env(data, "OLDPWD=", data->old_pwd); 
    }
    else
        perror("cd don't work");
}

void    ft_cd(t_data *data)
{
    int i = 0;
    while(data->matrice[i])
        i++;
    if(i == 1)
        ft_change_cd(data, getenv("HOME"));
    else if(ft_strcmp(data->matrice[1], "-") == 0)
        ft_change_cd(data, getenv("OLDPWD"));
    else if(data->matrice[1] != NULL)
        ft_change_cd(data, data->matrice[1]);        
}
*/