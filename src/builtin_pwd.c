#include "../header/minishell.h"

/* Gets current working directory and writes it to the corresponding output. */
void	builtin_pwd(t_vars *ms)
{
	char	*cwd;

	cwd = getcwd(NULL, PATH_MAX);
	if (cwd == NULL)
	{
		perror("pwd");
		return ;
	}
	write(ms->cmd->fd_out, cwd, ft_strlen(cwd));
	write(ms->cmd->fd_out, "\n", 1);
	free(cwd);
}
