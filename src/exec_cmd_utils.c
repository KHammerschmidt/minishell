/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mio <mio@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:28:01 by khammers          #+#    #+#             */
/*   Updated: 2022/03/15 21:38:11 by mio              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	create_tmp(t_vars *ms, t_cmd *current, char **tmp)
{
	*tmp = NULL;
	*tmp = ft_strdup(get_env_var(ms, "PWD")->content);
	*tmp = ft_strjoin(*tmp, "/");
	*tmp = ft_strjoin(*tmp, current->command[0]);
}

void	if_fail(t_vars *ms, t_cmd *current, char **tmp)
{
	ft_free_string(tmp);
	write(2, "Error: command not found: ", 26);
	ft_putstr_fd(current->command[0], 2);
	write(2, "\n", 1);
	ms->exit_status = 127;
}

int	if_paths(t_vars *ms, t_cmd *current, char **tmp, int *i)
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

int	check_if_dir(t_cmd *current)
{
	struct stat	path_stat;

	if (stat(current->execpath, &path_stat) == 0 \
		&& S_ISDIR(path_stat.st_mode))
	{
		printf("minishell: %s: is a directory\n", current->command[0]);
		return (1);
	}
	return (0);
}
