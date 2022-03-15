/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mio <mio@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:28:01 by khammers          #+#    #+#             */
/*   Updated: 2022/03/15 21:36:30 by mio              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Checks if command is accessible and, if so, sets execpath accordingly.   */
/* Also handles commands given as path from input. Returns error if command */
/* is not found or not accessible.                                          */
static int	check_cmd(t_vars *ms, t_cmd *current)
{
	int			i;
	char		*tmp;

	i = 0;
	create_tmp(ms, current, &tmp);
	if (current->command[0][0] == '/' || current->command[0][0] == '.' \
			|| current->command[0][0] == '~')
	{
		current->execpath = ft_strdup(current->command[0]);
		if (check_if_dir(current) == 1)
			return (1);
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
	if (current->command == NULL)
		ms->exit_status = 1;
	last_free(ms, 0);
	exit(ms->exit_status);
}
