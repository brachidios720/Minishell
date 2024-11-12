/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pag <pag@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:07:49 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/11/11 14:39:23 by pag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_get_env_value(char *name, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, name, ft_strlen(name)) == 0
			&& tmp->content[ft_strlen(name)] == '=')
			return (tmp->content + ft_strlen(name) + 1);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_change_env(t_env **env, char *name, char *new_value)
{
	t_env	*tmp;
	char	*new_content;
	int		name_len;
	int		value_len;
	int		total_len;

	tmp = *env;
	name_len = ft_strlen(name);
	value_len = ft_strlen(new_value);
	total_len = name_len + value_len + 2;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, name, name_len) == 0
			&& tmp->content[name_len] == '=')
		{
			new_content = (char *)malloc(sizeof(char) * total_len);
			if (!new_content)
				return ;
			ft_strcpy(new_content, name);
			new_content[name_len] = '=';
			ft_strcpy(new_content + name_len + 1, new_value);
			free(tmp->content);
			tmp->content = new_content;
			return ;
		}
		tmp = tmp->next;
	}
}

int	ft_change_directory(char *target_dir)
{
	if (chdir(target_dir) == 0)
		return (1);
	else
	{
		//perror("cd failed");
		return (0);
	}
}

void	ft_update_env(t_env **env, char *old_pwd, char *new_pwd)
{
	if (old_pwd)
		ft_change_env(env, "OLDPWD", old_pwd);
	if (new_pwd)
		ft_change_env(env, "PWD", new_pwd);
}

char	*ft_get_target_dir(char *target_dir, t_env **env)
{
	char	*home_dir;
	char	*old_pwd_dir;

	if (target_dir == NULL || ft_strcmp(target_dir, "~") == 0)
	{
		home_dir = ft_get_env_value("HOME", env);
		if (home_dir == NULL)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (NULL);
		}
		return (home_dir);
	}
	else if (ft_strcmp(target_dir, "-") == 0)
	{
		old_pwd_dir = ft_get_env_value("OLDPWD", env);
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
	int		i;
	char	*current_dir;
	char	*new_target_dir;
	char	*new_dir;

	i = 1;
	current_dir = getcwd(NULL, PATH_MAX);
	new_target_dir = ft_get_target_dir(target_dir[i], env);
	if (!new_target_dir)
	{
		free(current_dir);
		return ;
	}
	if (ft_change_directory(new_target_dir))
	{
		new_dir = getcwd(NULL, PATH_MAX);
		ft_update_env(env, current_dir, new_dir);
		free(new_dir);
	}
	free(current_dir);
}

void	init_pwd(t_env **env)
{
	char	*cwd;

	cwd = getcwd(NULL, PATH_MAX);
	ft_change_env(env, "PWD", cwd);
	ft_change_env(env, "OLDPWD", cwd);
	free(cwd);
}
