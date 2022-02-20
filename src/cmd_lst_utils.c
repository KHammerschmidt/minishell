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
	t_cmd *last;

	if (*cmd == NULL)
		*cmd = node;
	else
	{
		last = ft_lstlast_cmd(*cmd);
		last->next = node;
		node->previous = last;
	}
}

/* Passes on the information from command, fds and redirections 
to the struct t_cmd. */
void	pass_on_infos_node(t_info *info, t_cmd *node)
{
	node->command = info->command;
	node->pipe = info->pipe;
	node->input_op = info->input_op;
	node->output_op = info->output_op;
	node->fd_out = info->fd_out;
	node->fd_in = info->fd_in;
	node->infile = info->infile;
	node->outfile = info->outfile;
}

/* Creates a new node of type t_cmd. */
t_cmd	*ft_lstnew_cmd(t_info *info)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (node == NULL)
		return (NULL);
	pass_on_infos_node(info, node);
	node->next = NULL;
	node->previous = NULL;
	return (node);
}

// int ft_lstsize_cmd(t_cmd *lst)
// {
// 	t_cmd	*last;
// 	int		counter;

// 	counter = 0;
// 	last = lst;
// 	if (last == NULL)
// 		return (0);
// 	while (last->next != NULL)
// 	{
// 		last = last->next;
// 		counter++;
// 	}
// 	return (counter + 1);
// }
