#include "../header/minishell.h"

/* Checks if command is accessible and, if so, sets execpath accordingly.   */
/* Also handles commands given as path from input. Returns error if command */
/* is not found or not accessible.                                          */
int	check_cmd(t_vars *ms, t_cmd *current)
{
	int		i;

	i = 0;
	if (current->command[0][0] == '/' || current->command[0][0] == '.' \
			|| current->command[0][0] == '~')
	{
		current->execpath = ft_strdup(current->command[0]);						//mem alloc
		printf("%s\n", current->execpath);
		printf("%d\n", access(current->execpath, X_OK));
		if (access(current->execpath, X_OK) != 0)
		{
			perror("Error");
			ms->exit_status = errno;
			return (1);
		}
		return (0);
	}
	while (ms->paths[i] != NULL)
	{
		current->execpath = ft_strdup(ms->paths[i]);
		current->execpath = ft_strjoin(current->execpath, current->command[0]);		//mem alloc
		if (access(current->execpath, F_OK) == 0)
			return (0);
		ft_free_string(&current->execpath);
		i++;
	}
	write(2, "Error: command not found: ", 26);
	ft_putstr_fd(current->command[0], 2);
	write(2, "\n", 1);
	ms->exit_status = 127;
	return (1);
}

void	execute_cmd(t_vars *ms, t_cmd *current)
{
	if (ms->paths == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(current->command[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		ms->exit_status = 127;
		exit(ms->exit_status);
	}
	if (check_cmd(ms, current) == 0)
	{
		execve(current->execpath, current->command, ms->envp);
		perror("Error");
		ms->exit_status = errno;
	}
	exit(ms->exit_status);
}
