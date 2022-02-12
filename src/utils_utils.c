#include "../header/minishell.h"

void	ft_free_lst(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		lst = &(*lst)->next;
		free(tmp);
		tmp = *lst;
	}
}

int	ft_strchr_pos(const char *s, int c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (-1);
	while (s[i] != (unsigned char)c && s[i] != '\0')
		i++;
	if (s[i] == (unsigned char)c)
		return (i);
	else
		return (-1);
}

void	ft_free_string(char *str)
{
	if (str)
		free(str);
	str = NULL;
}

void	print_lst(t_vars *ms)
{
	t_cmd	*current;
	int		i;

	i = 0;
	current = NULL;
	current = ms->cmd;
	while (current && current->command != NULL)
	{
		i = 0;
		while (current->command[i] != NULL)
		{
			// printf("...%s...\n", current->command[i]);
			printf("command...%s... ", current->command[i]);
			i++;
		}
		printf("pipe: %d     infile: %s      outfile: %s\n", current->pipe, current->infile, current->outfile);
		current = current->next;
	}
}

void	free_cmd_struct(t_vars *ms)
{
	t_cmd	*current;

	current = NULL;
	while (current != NULL)								// Mio: Delete command table after each execution.
	{
		ft_free_strarray(current->command);				// Mio: Replace by function to empty and free the complete list
		current = current->next;
	}
	ms->cmd = NULL;										// Mio: Leaks?!
}