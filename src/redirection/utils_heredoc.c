/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pag <pag@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:42:12 by spagliar          #+#    #+#             */
/*   Updated: 2024/11/09 20:00:15 by pag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//configurer les signaux specifiquement pour le heredoc :
//remplace donc temprorairement les gestionnaires de signaux

void configure_heredoc_signals(void)
{
    struct sigaction sig_int;
    struct sigaction sig_quit;

    sig_int.sa_handler = &ft_handler_sig_hd;
    sigemptyset(&sig_int.sa_mask);
    sig_int.sa_flags = 0;

    sig_quit.sa_handler = SIG_IGN;  // Ignore `Ctrl+\` dans le here-document
    sigemptyset(&sig_quit.sa_mask);
    sig_quit.sa_flags = 0;

    // Applique les nouveaux gestionnaires de signaux
    sigaction(SIGINT, &sig_int, NULL);
    sigaction(SIGQUIT, &sig_quit, NULL);
}
// void configure_heredoc_signals() 
// {
//     struct sigaction sa;

//     // Initialise toute la structure `sigaction` à zéro
//     ft_memset(&sa, 0, sizeof(sa));
//     // Définir le gestionnaire de signal
//     sa.sa_handler = ft_handler_sig_hd;
//     // Initialise le masque de signaux pour ne bloquer aucun signal
//     sigemptyset(&sa.sa_mask);
//     // Définir les options (mettre à zéro ou définir selon vos besoins)
//     sa.sa_flags = 0;

//     // Configurer le signal SIGINT pour utiliser ce gestionnaire
//     if (sigaction(SIGINT, &sa, NULL) == -1) 
//     {
//         perror("Erreur lors de la config du signal SIGINT");
//         exit(EXIT_FAILURE);
//     }

//     // Configurer le signal SIGQUIT pour utiliser ce gestionnaire
//     if (sigaction(SIGQUIT, &sa, NULL) == -1) {
//         perror("Erreur lors de la config du signal SIGQUIT");
//         exit(EXIT_FAILURE);
//     }
// }

//lit les donnees jusqu au delimiteur et ecrit dans un fichier tmp
//restaure les signaux d origine a la fin
void read_input_with_heredoc(int tmp_fd, t_cmd *cmd)
{
    char *buffer;
    char *tmp_limite;
    tmp_limite = ft_strjoinn(cmd->delimiter, "\n");
    // struct sigaction old_int;
    // struct sigaction old_quit;
    //char	*tmp_limit;

	//tmp_limit = ft_strjoin(delimiter, "\n");
    //apl de fction pour sauvegarder les signaux actuels et configure les nveaux pour le heredoc
    configure_heredoc_signals();

    while(1)
    {
        //buffer = readline("heredoc> ");
        write(2, "heredoc> ", 9);
		buffer = get_next_line(STDIN_FILENO);
        //pas de fichier
        //printf("====== %d\n", g_signal);
        if (g_signal == 130)  // Si Ctrl+C a été déclenché, quitte immédiatement
        {
            free(buffer);
            break;
        }
        if(!buffer)
        {
            ft_putstr_fd("fin\n", STDIN_FILENO);
        }
        //verif ligne = delimiteur
        if (ft_strcmp(buffer, tmp_limite) == 0)
        {
            free (buffer);
            break;
        }
        ft_putstr_fd (buffer, tmp_fd);
        ft_putstr_fd ("\n", tmp_fd);

        free (buffer);
    }
    free (tmp_limite);
    //restaure les signaux d origine
    // if ((sigaction(SIGINT, &old_int, NULL)== -1) || sigaction(SIGQUIT, &old_quit, NULL)== -1)
    // {
    //     perror("erreur de restauration de signaux\n");
    // }
}
/*Ces fonctions permettent de gérer proprement les signaux pendant la lecture d'un 
here-document, en s'assurant que SIGINT a un comportement par défaut 
(ce qui permet généralement d'interrompre le here-document) et que SIGQUIT est ignoré,
tout en restaurant les gestionnaires de signaux originaux une fois la lecture terminée.*/
