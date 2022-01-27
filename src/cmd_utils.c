#include "../header/minishell.h"

/* Initialises the variables of t_cmd, allocates memory for the
**command variable as the size of size + 1. */
void	init_cmd(t_cmd *element, int size)
{
	element->op = 0;
	element->pipe = 0;
	element->command = ft_calloc(sizeof(*(element->command)), size + 1);
	if (!element->command)
		return ;										//Fehler einbauen!
	element->outfile = NULL;
	element->infile = NULL;
	element->errfile = NULL;
	element->next = NULL;
}

/* Searches for the last element of the list t_cmd */
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

/* Allocates memory for the new element (struct t_cmd) and initialises
the variables in init_cmd(). */
t_cmd	*ft_lstnew_cmd(int size)
{
	t_cmd	*new_element;

	new_element = malloc(sizeof(t_cmd));
	if (new_element == NULL)
		return (NULL);
	init_cmd(new_element, size);
	// new_element = &(t_cmd){0};
	return (new_element);
}

/* Handles new list element initialisation. If ms->cmd is empty, the new
element becomes the first one, otherwise it is appended to the end of
ms->cmd. */
t_cmd	*init_cmd_lst(t_vars *ms, int size)
{
	t_cmd	*last;
	t_cmd	*node;

	node = ft_lstnew_cmd(size);
	if (ms->cmd == NULL)
		ms->cmd = node;
	else
	{
		last = ft_lstlast_cmd(ms->cmd);
		last->next = node;
	}
	return (node);
}
