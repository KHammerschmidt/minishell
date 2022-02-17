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
		node->previous = last;							//added previous node == last node of list
	}
}

/* Open any files related to infile and outfile redirections. */
void	open_files(t_cmd *node)
{
	if (node->input_op == -1)
	{
		if (access(node->infile, F_OK) != 0)
		{
			if (access(node->infile, R_OK) != 0)
				perror("Error");
			else
			{
				ft_putstr_fd("zsh: No such file or directory: ", 2);
				ft_putendl_fd(node->infile, 2);
			}
		}
		else
		{
			node->fd_in = open(node->infile, O_RDONLY);
			if (node->fd_in == -1)
				perror("Error: ");
		}
	}
	if (node->output_op != 0)
	{
		if (node->output_op == -1)
			node->fd_out = open(node->outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (node->output_op == -2)
			node->fd_out = open(node->outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (node->fd_out == -1 || access(node->outfile, W_OK) != 0)
			perror("Error");
	}
}

/* Passes on the information about the command into the struct t_cmd. */
void	pass_on_infos_node(t_info *info, t_cmd *node)
{
	node->command = info->command;
	node->pipe = info->pipe;
											//dups oder einfach Gleichzeichen?????
	node->fd_out = 1;
	node->fd_in = 0;
	node->input_op = info->input_op;
	node->output_op = info->output_op;
	node->infile = info->infile;
	node->outfile = info->outfile;
	open_files(node);
	reset_info_struct(info);
}

t_cmd	*ft_lstnew_cmd(t_info *info)				//das hier wieder rein (neue lst_new)
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

int ft_lstsize_cmd(t_cmd *lst)
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
