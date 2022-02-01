#include "../header/minishell.h"

/* Prints the char **command in every element of the list. */
void	print_cmd_lst(t_vars *ms)				//meins
{
	t_cmd *current;

	current = ms->cmd;
	int	i = 0;
	while (current != NULL)
	{
		i = 0;
		printf("New command\n");						// Mio: For testing purposes only.
		while (current->command[i] != NULL)
		{
			printf("...%s...\n", current->command[i]);
			i++;
		}
		current = current->next;
	}
}

// /* Initialises the variables of t_cmd, allocates memory for the
// **command variable as the size of size + 1. */
// void	init_cmd(t_cmd *node, int size, char **arr)
// {
// 	node->op = 0;
// 	node->pipe = 0;
// 	node->command = NULL;
// 	// node->command = ft_calloc(sizeof(*(node->command)), size + 1);
// 	// if (!node->command)
// 	// 	return ;										//Fehler einbauen!
// 	node->command = arr;
// 	node->outfile = NULL;
// 	node->infile = NULL;
// 	node->errfile = NULL;
// 	node->next = NULL;
// 	if (!size)
// 		printf("\n");
// }

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

void	pass_on_infos_node(t_info *info, t_cmd *node)
{
	node->command = info->command;
	node->pipe = info->pipe;
	node->op = info->op;
	node->infile = info->infile;
	node->outfile = info->outfile;
	node->errfile = info->errfile;
	reset_info_struct(info);
	printf("HERE\n");
}

// t_cmd	*ft_lstnew_cmd(t_info *info)
// {
// 	t_cmd	*node;

// 	node = malloc(sizeof(t_cmd));
// 	if (node == NULL)
// 		return (NULL);
// 	// init_cmd(node, size, command);
// 	pass_on_infos_node(info, node);
// 	// node->command = ms->cmd->command;
// 	// node->pipe = ms->cmd->pipe;
// 	node->next = NULL;
// 	// node->outfile = NULL;
// 	// node->infile = NULL;
// 	// node->errfile = NULL;
// 	// node->next = NULL;
// 	// node->op = 0;
// 	// node->pipe = 0;
// 	// node->command = NULL;
// 	return (node);
// }

t_cmd	*ft_lstnew_cmd(char **command)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (node == NULL)
		return (NULL);
	// init_cmd(node, size, command);
	node->command = command;
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











/* Allocates memory for the new node (struct t_cmd) and initialises
the variables in init_cmd(). */
// t_cmd	*ft_lstnew_cmd(int size)
// {
// 	t_cmd	*new_node;

// 	new_node = malloc(sizeof(t_cmd));
// 	if (new_node == NULL)
// 		return (NULL);
// 	init_cmd(new_node, size);
// 	// new_node = &(t_cmd){0};
// 	return (new_node);
// }

/* Handles new list node initialisation. If ms->cmd is empty, the new
node becomes the first one, otherwise it is appended to the end of
ms->cmd. */
// t_cmd	*init_cmd_lst(t_vars *ms, int size)
// {
// 	t_cmd	*last;
// 	t_cmd	*node;

// 	node = ft_lstnew_cmd(size);
// 	if (ms->cmd == NULL)
// 		ms->cmd = node;
// 	else
// 	{
// 		last = ft_lstlast_cmd(ms->cmd);
// 		last->next = node;
// 	}
// 	return (node);
// }
