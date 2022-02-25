#include "../header/minishell.h"

/* Returns last node in the t_cmd list. */
t_cmd	*ft_lstlast_cmd(t_cmd *lst)
{
	t_cmd	*last;

	last = lst;
	if (last == NULL)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

/* Adds a node to the back of a list t_cmd. */
void	ft_lstadd_back_cmd(t_cmd **cmd, t_cmd *node)
{
	t_cmd	*last;

	if (*cmd == NULL)
		*cmd = node;
	else
	{
		last = ft_lstlast_cmd(*cmd);
		last->next = node;
		node->previous = last;
	}
}

/* Creates a new node of type t_cmd. */
t_cmd	*ft_lstnew_cmd(t_vars *ms)
{
	t_cmd	*node;

	node = ft_calloc(sizeof(t_cmd), 1);
	if (node == NULL)
		return (NULL);
	pass_on_infos_node(ms, node);
	node->next = NULL;
	node->previous = NULL;
	return (node);
}

int	ft_lstsize_cmd(t_cmd *lst)
{
	t_cmd	*last;
	int		counter;

	counter = 0;
	last = lst;
	if (last == NULL)
		return (0);
	while (last->next != NULL)
	{
		last = last->next;
		counter++;
	}
	return (counter + 1);
}
