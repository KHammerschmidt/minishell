#include "../header/minishell.h"

/* Writes envar list to corresponding output. */
void	builtin_env(t_vars *ms, t_cmd *current)
{
	t_env	*tmp;

	tmp = ms->env;
	while (tmp != NULL)
	{
		write(current->fd_out, tmp->name, ft_strlen(tmp->name));
		write(current->fd_out, "=", 1);
		write(current->fd_out, tmp->content, ft_strlen(tmp->content));
		write(current->fd_out, "\n", 1);
		tmp = tmp->next;
	}
}
