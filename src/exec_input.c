#include "../header/minishell.h"

/* Checks if command is accessible and, if so, sets path accordingly.       */
/* Also handles commands given as path from input. Returns error if command */
/* is not found or not accessible.                                          */
int	check_cmd(t_vars *ms, t_cmd *current)
{
	int		i;

	i = 0;
	if (current->command[0][0] == '/')
	{
		current->execpath = ft_strdup(current->command[0]);
		if (!current->execpath)
			free_and_exit(ms, 1, 1);	//hier gucken was weiter gegeben wird
		printf("%s\n", current->execpath);
		return (0);
	}
	while (ms->paths[i] != NULL)
	{
		current->execpath = ft_strjoin(ms->paths[i], current->command[0]);
		if (!current->execpath)
			free_and_exit(ms, 1, 1);
		// printf("%s\n", current->execpath);
		if (access(current->execpath, F_OK) == 0)
			return (0);
		free(current->execpath);
		i++;
	}
	write(2, "Error: command not found: ", 26);
	ft_putstr_fd(current->command[0], 2);
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
