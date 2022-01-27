#include "../header/minishell.h"

/* Writes given string to correponding output, omitting the new line if -n */
/* is given as option.                                                     */
int	builtin_echo(t_vars *ms, char **arg_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (arg_str != NULL)
	{
		while (arg_str[i] != NULL)
			i++;
	}
	if (arg_str == NULL)
	{
		write(ms->fd_out, "\n", 1);
		return (0);					// set exit code and back to pipe or STDIN
	}
	if (i == 1)
	{
		if (compare_str(arg_str[0], "-n") == 0)
		{
			return (0);
		}
		ft_putstr_fd(arg_str[0], ms->fd_out);
		ft_putchar_fd('\n', ms->fd_out);
		return (0);					// set exit code and back to pipe or STDIN
	}
	else if (i > 1)
	{
		if (compare_str(arg_str[0], "-n") == 0)
		{
			while (i > 0)
			{
				ft_putstr_fd(arg_str[j + 1], ms->fd_out);
				ft_putchar_fd(' ', ms->fd_out);
				j++;
				i--;
			}
		}
		else
		{
			while (i > 0)
			{
				ft_putstr_fd(arg_str[j], ms->fd_out);
				ft_putchar_fd(' ', ms->fd_out);
				j++;
				i--;
			}
			ft_putchar_fd('\n', ms->fd_out);
		}
	}
	return (1);
}
