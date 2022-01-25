#include "../header/minishell.h"

/* Looks for var_name in envar list and deletes the respective node if found. */
int	builtin_unset(t_vars *ms, char *var_name)
{
	t_env	*current;
	t_env	*prev;

	current = ms->env;
	prev = NULL;
	if (current == NULL)
	{
		write(2, "Error. No environment variables found.\n", 39);
		return (1);
	}
	if (compare_str(current->name, var_name) == 0)
	{
		ms->env = current->next;
		free(current->name);
		free(current->content);
		free(current);
		return (0);
	}
	prev = current;
	current = current->next;
	while (current != NULL)
	{
		if (compare_str(current->name, var_name) == 0)
		{
			prev->next = current->next;
			free(current->name);
			free(current->content);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}
