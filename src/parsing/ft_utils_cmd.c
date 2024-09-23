#include "../../include/minishell.h"

void	ft_lst_addbackk(t_cmd **stack, t_cmd *node)
{
	t_cmd	*tmp;

	tmp = (*stack);
	if (tmp == NULL)
	{
		(*stack) = node;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
	node->next = NULL;
}

int	ft_lstsizee(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}

void ft_lstclearr(t_cmd **cmd)
{
    t_cmd *tmp;

    while (*cmd)
    {
        tmp = (*cmd)->next;
        free(*cmd);
        *cmd = tmp;
    }
}

void ft_free(char *str, t_cmd **cmd)
{
	ft_lstclearr(cmd);
	free(str);
}
