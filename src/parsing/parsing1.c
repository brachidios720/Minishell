#include "../../include/minishell.h"

t_cmd	*ft_lsttnew(t_data *data, int i)
{
	t_cmd	*newnode;

	newnode = malloc(sizeof(t_cmd));
	if (!newnode)
		return (NULL);
	newnode->str = ft_strdup(data->cut_matrice[i]);
	if (!newnode->str)
    {
        free(newnode);
        return (NULL);
    }
    newnode->num = i;
    // newnode->option = who;
	newnode->next = NULL;
	return (newnode);
}

void	ft_do_all(char *str, t_cmd **cmd, t_data *data, t_cmd *new_node)
{
	ft_cut_cont(str, data);
	int i = 0;
	while(data->cut_matrice[i])
    {
        new_node = ft_lsttnew(data, i);
        i++;
        ft_lst_addbackk(cmd, new_node);
    }
}

