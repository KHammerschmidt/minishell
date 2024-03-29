/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process_loop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:17:14 by khammers          #+#    #+#             */
/*   Updated: 2022/03/14 19:05:39 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Checks the command array to see if there is a command to be executed,
if not save == -1 || save == -2 when an error occured, if it's a builtin
as a single command save == -3. When it is a simple command or various
builtins 0 is returned. save == 1 indicates that current->command is not
valid to be executed, but there might be one in the next list element. */
static int	check_cmd_table(t_cmd *current, t_vars *ms, int *save)
{
	if (current->command == NULL && current->next == NULL)
	{
		*save = -1;
		return (*save);
	}
	if (current->flag == -1)
	{
		ms->exit_status = 1;
		if (current->next == NULL)
		{
			*save = -2;
			return (*save);
		}
		*save = 1;
		return (*save);
	}
	if (current->next == NULL && current->previous == NULL
		&& is_builtin(ms, current->command[0]) == 1)
	{
		*save = -3;
		return (*save);
	}
	return (0);
}

/* Returns 0 if the current and the next command are not to be executed,
returns the exit_status in case the command is not valid or executes a
buildin and returns it's exit status when it's a single command. */
static int	get_return_value(t_vars *ms, int save, t_cmd *current)
{
	if (save == -1)
		return (0);
	if (save == -2)
		return (ms->exit_status);
	if (save == -3)
		return (ft_builtin_parent(current, ms));
	return (0);
}

/* Loops through the command table.
The function check_cmd_table() checks whether there is a command to be
executed or if there is a special case, e.g. only one builtin commadn.
If this is the case the respective return value is called. If there is
a simple command to be executed (save == 5), ft_processes() is called to
execute the command within a child process. The parent process waits for
every process pid to capture the last process' exit status. */
int	execution_process_loop(t_vars *ms)
{
	int		i;
	int		save;
	pid_t	pid;
	t_cmd	*current;

	i = 0;
	pid = 0;
	save = 0;
	current = ms->cmd;
	while (current != NULL)
	{
		if (check_cmd_table(current, ms, &save) < 0)
			return (get_return_value(ms, save, current));
		if (save == 0)
			ft_processes(ms, current, &pid);
		current = current->next;
	}
	while (i != -1)
	{
		i = waitpid(0, &save, 0);
		if (i == pid)
			ms->exit_status = save;
	}
	return (WEXITSTATUS(ms->exit_status));
}
