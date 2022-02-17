#include "../header/minishell.h"

/* Gets current working directory and writes it to the corresponding output. */
int	builtin_pwd(t_vars *ms, t_cmd *current)
{
	char	*cwd;

	(void)ms;
	cwd = getcwd(NULL, PATH_MAX);
	if (cwd == NULL)
	{
		current->error_flag = 1;
		current->error_msg = ft_strdup(strerror(errno));
		return (1);
	}
	write(current->fd_out, cwd, ft_strlen(cwd));
	write(current->fd_out, "\n", 1);
	free(cwd);
	return (0);
}
