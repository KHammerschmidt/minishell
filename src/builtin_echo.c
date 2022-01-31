#include "../header/minishell.h"

int	find_n_flag(t_vars *ms)
{
	if (ms->cmd->command[1] != NULL)
	{
		if (ft_strncmp(ms->cmd->command[1], "-n", ft_strlen(ms->cmd->command[1])) == 0)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

/* Writes given string to correponding output, omitting the new line if -n */
/* is given as option.                                                     */
int	builtin_echo(t_vars *ms)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if ((n_flag = find_n_flag(ms)) == 1)
		i++;
	if (ms->cmd->command[1] != NULL)
	{
		if (n_flag == 1 && ms->cmd->command[2] == NULL)
			return (0);
	}
	while (ms->cmd->command[i] != NULL)
	{
		ft_putstr_fd(ms->cmd->command[i], ms->cmd->fd_out);
		ft_putchar_fd(' ', ms->cmd->fd_out);
		i++;
	}
	if (n_flag == 0)
		ft_putchar_fd('\n', ms->cmd->fd_out);
	return (0);
}
