#include "../header/minishell.h"

/* Writes given string to correponding output, omitting the new line if -n */
/* is given as option.                                                     */
void	builtin_echo(t_vars *ms, char *str, int no_nl_flag)
{
	int	i;

	i = 0;
	if (no_nl_flag == 0)
	{
		ft_putstr_fd(str, ms->fd_out);
		ft_putchar_fd('\n', ms->fd_out);
	}
	else
		ft_putstr_fd(str, ms->fd_out);
}
