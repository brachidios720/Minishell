#include "../../include/minishell.h"

// void	ft_chaine_pipe_utils(int pipe_fd[2], t_cmd **cmd, t_data *data, int command_index)
// {
// 	t_cmd	*tmp;
// 	int		prev_fd;

// 	tmp = *cmd;
// 	prev_fd = -1;
// 	if (command_index == 0)//Première commande
// 		ft_pipe_first_cmd(pipe_fd, tmp);
// 	else if (tmp->next == NULL)//Dernière commande
// 		ft_pipe_last_cmd((int[2] ){prev_fd, pipe_fd[1]}, tmp);
// 	if (tmp->next != NULL && tmp != *cmd) // Commande intermédiaire
// 		ft_pipe_middle_cmd(prev_fd, pipe_fd);
// 	execute_command_or_builtin(&tmp, &data->copy_env, data);
// }
