#include "../header/minishell.h"

/* Returns last node in a list. */
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

/* Adds item to the back of a list. */
void	ft_lstadd_back_cmd(t_cmd **cmd, t_cmd *node)
{
	t_cmd *last;

	if (*cmd == NULL)
		*cmd = node;
	else
	{
		last = ft_lstlast_cmd(*cmd);
		last->next = node;
	}
}

/* Passes on the information about the command into the struct t_cmd. */
void	pass_on_infos_node(t_info *info, t_cmd *node)
{
	node->command = info->command;
	node->pipe = info->pipe;
	node->op = info->op;
	node->infile = info->infile;
	node->outfile = info->outfile;
	node->errfile = info->errfile;
	reset_info_struct(info);
}

t_cmd	*ft_lstnew_cmd(t_info *info)				//das hier wieder rein (neue lst_new)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (node == NULL)
		return (NULL);
	// init_cmd(node, size, command);
	pass_on_infos_node(info, node);
	// node->command = ms->cmd->command;
	// node->pipe = ms->cmd->pipe;
	node->next = NULL;
	// node->outfile = NULL;
	// node->infile = NULL;
	// node->errfile = NULL;
	// node->next = NULL;
	// node->op = 0;
	// node->pipe = 0;
	// node->command = NULL;
	return (node);
}