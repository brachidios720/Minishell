/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <spagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:42:12 by spagliar          #+#    #+#             */
/*   Updated: 2024/11/09 15:31:43 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//configurer les signaux specifiquement pour le heredoc :
//remplace donc temprorairement les gestionnaires de signaux
void configure_heredoc_signals() 
{
    struct sigaction sa;

    // Initialise toute la structure `sigaction` à zéro
    ft_memset(&sa, 0, sizeof(sa));
    // Définir le gestionnaire de signal
    sa.sa_handler = ft_handler_sig_hd;
    // Initialise le masque de signaux pour ne bloquer aucun signal
    sigemptyset(&sa.sa_mask);
    // Définir les options (mettre à zéro ou définir selon vos besoins)
    sa.sa_flags = 0;

    // Configurer le signal SIGINT pour utiliser ce gestionnaire
    if (sigaction(SIGINT, &sa, NULL) == -1) 
    {
        perror("Erreur lors de la config du signal SIGINT");
        exit(EXIT_FAILURE);
    }

    // Configurer le signal SIGQUIT pour utiliser ce gestionnaire
    if (sigaction(SIGQUIT, &sa, NULL) == -1) {
        perror("Erreur lors de la config du signal SIGQUIT");
        exit(EXIT_FAILURE);
    }
}

//lit les donnees jusqu au delimiteur et ecrit dans un fichier tmp
//restaure les signaux d origine a la fin
void read_input_with_heredoc(int tmp_fd, t_cmd *cmd)
{
    char *buffer;
    struct sigaction old_int;
    struct sigaction old_quit;

    //apl de fction pour sauvegarder les signaux actuels et configure les nveaux pour le heredoc
    configure_heredoc_signals(&old_int, &old_quit);

    //Lit l'entrée ligne par ligne jusqu'à rencontrer le délimiteur, écrivant chaque ligne dans le fichier temporaire.
    ft_putstr_fd("> ", STDOUT_FILENO);
    buffer = get_next_line(STDIN_FILENO);
    while (buffer && ft_strcmp(buffer, cmd->delimiter) != 0)
    {
        ft_putstr_fd(buffer, tmp_fd);
        free(buffer);
        ft_putstr_fd("> ", STDOUT_FILENO);
        buffer = get_next_line(STDIN_FILENO);
    }
    //Gère le cas où la fin du fichier est atteinte sans rencontrer le délimiteur.
    if (buffer)
        free(buffer);
    //Restaure les gestionnaires de signaux d'origine à la fin de la fonction.
    else
        ft_putstr_fd("delimiter fin de fichier\n", STDERR_FILENO);

    // Restauration des signaux d'origine
    sigaction(SIGINT, &old_int, NULL);
    sigaction(SIGQUIT, &old_quit, NULL);
}
/*Ces fonctions permettent de gérer proprement les signaux pendant la lecture d'un 
here-document, en s'assurant que SIGINT a un comportement par défaut 
(ce qui permet généralement d'interrompre le here-document) et que SIGQUIT est ignoré,
tout en restaurant les gestionnaires de signaux originaux une fois la lecture terminée.*/
