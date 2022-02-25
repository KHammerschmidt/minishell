#include "../header/minishell.h"

/* Gets current working directory and writes it to the corresponding output. */
int	builtin_pwd(t_vars *ms, t_cmd *current)
{
	char	*cwd;

	(void)ms;
	cwd = getcwd(NULL, PATH_MAX);
	if (cwd == NULL)
	{
		ms->exit_status = errno;
		return (ms->exit_status);
	}
	write(current->fd_out, cwd, ft_strlen(cwd));
	write(current->fd_out, "\n", 1);
	free(cwd);
	return (0);
}
