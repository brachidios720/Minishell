/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:07:49 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/10 17:15:43 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    ft_cd(char *path)
{
    char *old_pwd = getenv("PWD");
    char cwd[PATH_MAX];
    
    if(path == NULL || strcmp(path, "") == 0)
        path = getenv("HOME");
    if(ft_strcmp(path, "-"))
        getenv("OLD_PWD");
        if(path == NULL)
            return;
    if(chdir(path) != 0)
    {
        printf("error\n");
        return;
    }
    setenv("OLD_PWD", old_pwd, 1);
    if(getcwd(cwd, sizeof(cwd)) != NULL)
        setenv("PWD", cwd, 1);
    else
        perror(cwd);
}