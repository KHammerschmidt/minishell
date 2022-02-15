#include "../header/minishell.h"

/* Checks if command is accessible and, if so, sets path accordingly.       */
/* Also handles commands given as path from input. Returns error if command */
/* is not found or not accessible.                                          */
int	check_cmd(t_vars *ms, char **cmd)
{
	int		i;

	i = 0;
	if (cmd[0][0] == '/')
	{
		ms->cmd->execpath = ft_strdup(cmd[0]);
		if (!ms->cmd->execpath)
			free_and_exit(ms, 1, 1);
		printf("%s\n", ms->cmd->execpath);
		return (0);
	}
	while (ms->paths[i] != NULL)
	{
		ms->cmd->execpath = ft_strjoin(ms->paths[i], cmd[0]);
		if (!ms->cmd->execpath)
			free_and_exit(ms, 1, 1);
		// printf("%s\n", ms->cmd->execpath);
		if (access(ms->cmd->execpath, F_OK) == 0)
			return (0);
		free(ms->cmd->execpath);
		i++;
	}
	write(2, "Error: command not found: ", 26);
	ft_putstr_fd(cmd[0], 2);
	write(2, "\n", 1);
	// free_and_exit(ms, 1, 127);
	return (1);
}

int	get_paths(t_vars *ms)
{
	int		i;
	t_env	*current;

	i = 0;
	current = ms->env;
	while (current != NULL)
	{
		if (compare_str(current->name, "PATH") == 0)
		{
			ms->paths = ft_split(current->content, ':');
			if (!ms->paths)
				// free_and_exit(ms, 1, 1);
				return (1);				// change to correct exit code
			break ;
		}
		current = current->next;
	}
	i = 0;
	while (ms->paths[i] != NULL)
	{
		ms->paths[i] = ft_strjoin(ms->paths[i], "/");
		// if (!ms->paths)							// brauchen wir das? wozu?
		// 	free_and_exit(ms, 1, 1);				// change to correct exit code
		i++;
	}
	return (0);
}
