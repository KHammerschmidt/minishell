#include "../header/minishell.h"

/* Writes envar list to corresponding output. */
void	builtin_env(t_vars *ms)
{
	t_env	*current;

	current = ms->env;
	while (current != NULL)
	{
		write(ms->fd_out, current->name, ft_strlen(current->name));
		write(ms->fd_out, "=", 1);
		write(ms->fd_out, current->content, ft_strlen(current->content));
		write(ms->fd_out, "\n", 1);
		current = current->next;
	}
}
