#include "../header/minishell.h"

static void	create_tmp(t_vars *ms, t_cmd *current, char **tmp)
{
	*tmp = NULL;
	*tmp = ft_strdup(get_env_var(ms, "PWD")->content);
	*tmp = ft_strjoin(*tmp, "/");
	*tmp = ft_strjoin(*tmp, current->command[0]);
}

static void	if_fail(t_vars *ms, t_cmd *current, char **tmp)
{
	ft_free_string(tmp);
	write(2, "Error: command not found: ", 26);
	ft_putstr_fd(current->command[0], 2);
	write(2, "\n", 1);
	ms->exit_status = 127;
}

static int	if_paths(t_vars *ms, t_cmd *current, char **tmp, int *i)
{
	if (ms->paths != NULL)
	{
		while (ms->paths[*i] != NULL)
		{
			current->execpath = ft_strdup(ms->paths[*i]);
			current->execpath = ft_strjoin(current->execpath, \
				current->command[0]);
			if (access(current->execpath, F_OK) == 0)
			{
				ft_free_string(tmp);
				return (1);
			}
			ft_free_string(&current->execpath);
			(*i)++;
		}
	}
	return (0);
}

/* Checks if command is accessible and, if so, sets execpath accordingly.   */
/* Also handles commands given as path from input. Returns error if command */
/* is not found or not accessible.                                          */
static int	check_cmd(t_vars *ms, t_cmd *current)
{
	int		i;
	char	*tmp;

	i = 0;
	create_tmp(ms, current, &tmp);
	if (current->command[0][0] == '/' || current->command[0][0] == '.' \
			|| current->command[0][0] == '~')
	{
		current->execpath = ft_strdup(current->command[0]);
		ft_free_string(&tmp);
		return (0);
	}
	if (access(tmp, F_OK) == 0)
	{
		current->execpath = tmp;
		ft_free_string(&tmp);
		return (0);
	}
	if (if_paths(ms, current, &tmp, &i) == 1)
		return (0);
	if_fail(ms, current, &tmp);
	return (1);
}

void	execute_cmd(t_vars *ms, t_cmd *current)
{
	if (check_cmd(ms, current) == 0)
	{
		execve(current->execpath, current->command, ms->envp);
		perror("Error");
		ms->exit_status = errno;
	}
	exit(ms->exit_status);
}
