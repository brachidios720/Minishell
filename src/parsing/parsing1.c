#include "../../include/minishell.h"

t_cmd	*ft_lsttnew(void *content, t_data *data)
{
	t_cmd	*newnode;
    int i = 0;

	newnode = malloc(sizeof(t_cmd));
	if (!newnode)
	{
		return (NULL);
	}
	newnode->str = ;
    newnode->num = ;
    newnode->option = ;
	newnode->next = NULL;
	return (newnode);
}