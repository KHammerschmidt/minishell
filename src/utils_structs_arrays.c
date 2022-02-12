#include "../header/minishell.h"

/* Creates new list element, including allocating memory, */
/* which can then be added to a list. */
static t_cmd	*new_element(char **command)
{
	t_cmd	*new_element;

	new_element = malloc(sizeof(t_cmd));
	if (new_element == NULL)
		return (NULL);
	new_element->command = command;
	new_element->fd_out = 1;					// Mio: For testing purposes only.
	new_element->next = NULL;
	return (new_element);
}

/* Returns last element in a list. */
static t_cmd	*lastelement(t_cmd *lst)
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
static void	add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = lastelement(*lst);
	last->next = new;
}

void	save_commands(t_vars *ms)
{
	int		i;
	int		j;
	char	*tmp;
	t_cmd	*new;
	// t_cmd	*current;

	i = 0;
	j = 0;
	if ((i = ft_strchr_pos(ms->cmd_line, '|')) == -1)
	{
		new = new_element(ft_split(ms->cmd_line, ' '));
		add_back(&ms->cmd, new);
	}
	else
	{
		while (i != -1)
		{
			i = ft_strchr_pos(&ms->cmd_line[j], '|');
			tmp = ft_substr(ms->cmd_line, j, i);
			new = new_element(ft_split(tmp, ' '));
			add_back(&ms->cmd, new);
			free(tmp);
			j += i + 1;
			// open issue: delete white spaces
		}
	}
	i = 0;
	// current = ms->cmd;
	// while (current != NULL)
	// {
	// 	i = 0;
	// 	printf("New command\n");						// Mio: For testing purposes only.
	// 	while (current->command[i] != NULL)
	// 	{
	// 		printf("%s\n", current->command[i]);
	// 		i++;
	// 	}
	// 	current = current->next;
	// }
}
