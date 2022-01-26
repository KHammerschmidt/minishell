#include "../header/minishell.h"

void	init_cmd(t_cmd *element)
{
	element->index = 0;
	element->op = 0;
	element->pipe = 0;
	element->command = NULL;
	element->args = NULL;
	element->outfile = NULL;
	element->infile = NULL;
	element->errfile = NULL;
	element->next = NULL;
}

t_cmd	*ft_lstlast_cmd(t_cmd *lst)			//mio
{
	t_cmd	*last;

	last = lst;
	if (last == NULL)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

// void	ft_lstadd_back_cmd(t_cmd *lst, t_cmd *new)
// {
// 	t_cmd	*last;

// 	last = ft_lstlast_cmd(lst);
// 	last->next = new;
// }

t_cmd	*ft_lstnew_cmd(void)
{
	t_cmd	*new_element;

	new_element = malloc(sizeof(t_cmd));
	// new_element = &(t_cmd){0};
	if (new_element == NULL)
		return (NULL);
	init_cmd(new_element);
	return (new_element);
}