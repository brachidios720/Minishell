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

char *ft_get_env_value(char *name, t_env **env)
{
    t_env *tmp = *env;
    
    while (tmp)
    {
        if (ft_strncmp(tmp->content, name, ft_strlen(name)) == 0 && tmp->content[ft_strlen(name)] == '=')
            return (tmp->content + ft_strlen(name) + 1); 
        tmp = tmp->next;
    }
    return (NULL);
}

void ft_change_env(t_env **env, char *name, char *new_value)
{
    t_env *tmp = *env;
    char *new_content;
    int name_len = ft_strlen(name);
    int value_len = ft_strlen(new_value);
    int total_len = name_len + value_len + 2;

    while (tmp)
    {
        if (ft_strncmp(tmp->content, name, name_len) == 0 && tmp->content[name_len] == '=')
        {
            new_content = (char *)malloc(sizeof(char) * total_len);
            if (!new_content)
                return;
            ft_strcpy(new_content, name);
            new_content[name_len] = '=';
            ft_strcpy(new_content + name_len + 1, new_value);
        
            free(tmp->content);
            tmp->content = new_content;
            return;
        }
        tmp = tmp->next;
    }
}

int ft_change_directory(char *target_dir)
{
    if (chdir(target_dir) == 0)
        return (1); 
    else
    {
        perror("cd failed"); 
        return (0);
    }
}

void ft_update_env(t_env **env, char *old_pwd, char *new_pwd)
{
    if (old_pwd)
        ft_change_env(env, "OLDPWD", old_pwd);
    if (new_pwd)
        ft_change_env(env, "PWD", new_pwd);
}

char *ft_get_target_dir(char *target_dir, t_env **env)
{
    if (target_dir == NULL || ft_strcmp(target_dir, "~") == 0)
    {
        char *home_dir = ft_get_env_value("HOME", env);
        if (home_dir == NULL)
        {
            ft_putstr_fd("cd: HOME not set\n", 2);
            return (NULL);
        }
        return (home_dir);
    }
    else if (ft_strcmp(target_dir, "-") == 0)
    {
        char *old_pwd_dir = ft_get_env_value("OLDPWD", env);
        if (old_pwd_dir == NULL)
        {
            ft_putstr_fd("cd: OLDPWD not set\n", 2);
            return (NULL);
        }
        return (old_pwd_dir);
    }
    return (target_dir);
}

void ft_cd(t_env **env, char **target_dir)
{
    int i = 1;
    char *current_dir = getcwd(NULL, PATH_MAX); 
    char *new_target_dir = ft_get_target_dir(target_dir[i], env);

    if (!new_target_dir) 
    {
        free(current_dir);
        return;
    }

    if (ft_change_directory(new_target_dir))
    {
        char *new_dir = getcwd(NULL, PATH_MAX);
        ft_update_env(env, current_dir, new_dir);
        free(new_dir);
    }

    free(current_dir);
}

void init_pwd(t_env **env)
{
    char *cwd = getcwd(NULL, PATH_MAX);

    ft_change_env(env, "PWD", cwd);
    ft_change_env(env, "OLDPWD", cwd);

    free(cwd);
}
