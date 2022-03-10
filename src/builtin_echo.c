#include "../header/minishell.h"

int	find_n_flag(t_vars *ms)
{
	if (ms->cmd->command[1] != NULL)
	{
		if (compare_str(ms->cmd->command[1], "-n") == 0)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

/* Writes given string to correponding output, omitting the new line if -n */
/* is given as option.                                                     */
int	builtin_echo(t_vars *ms, t_cmd *current)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	n_flag = find_n_flag(ms);
	if (n_flag == 1)
		i++;
	if (current->command[1] != NULL)
	{
		if (n_flag == 1 && current->command[2] == NULL)
			return (0);
	}
	while (current->command[i] != NULL)
	{
		ft_putstr_fd(current->command[i], current->fd_out);
		if (current->command[i + 1] != NULL)
			ft_putchar_fd(' ', current->fd_out);
		i++;
	}
	if (n_flag == 0)
		ft_putchar_fd('\n', current->fd_out);
	return (0);
}
