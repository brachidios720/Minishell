/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:54:54 by raphaelcarb       #+#    #+#             */
/*   Updated: 2024/09/17 15:25:27 by raphaelcarb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int ac, char **av, char **envp)
{
    t_data *data = NULL;
    t_cmd *cmd = NULL;
    t_env *env = NULL;
    (void)ac;

    print_minishell();  // Affiche l'invite du shell

    // Allocation et initialisation des données
    data = malloc(sizeof(t_data));
    if (data == NULL)
    {
        perror("Erreur d'allocation mémoire pour data");
        return (1);
    }

    env = init_env(envp);  // Initialiser les variables d'environnement
    init_pwd(&env);
    // Boucle principale du shell
    ft_check_line(av, envp, data, &cmd, &env);

    // Libérer la mémoire avant de quitter
    free(cmd);
    free(data);

    return (0);
}
