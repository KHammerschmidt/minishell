/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:34:30 by mortmeie          #+#    #+#             */
/*   Updated: 2021/11/19 16:46:13 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

/* Checks if PATH is set in **envp to prevent segfault when */
/* 'unset path' is used.                                    */
int	check_envp(char **envp)
{
	int	i;

	i = 0;
	while (1)
	{
		if (envp[i] == NULL)
		{
			write(2, "Error: Path not found.\n", 23);
			exit(EXIT_FAILURE);
		}
		else if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		else
			i++;
	}
	return (0);
}

/* Checks if command is accessible and, if so, sets cmd_path accordingly.   */
/* Also handles commands given as path from input. Returns error if command */
/* is not found or not accessible.                                          */
int	check_cmd(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->cmd[0][0] == '/')
	{
		vars->cmd_path = ft_strdup(vars->cmd[0]);
		if (!vars->cmd_path)
			exit_on_error(vars);
		return (0);
	}
	while (vars->my_paths[i] != NULL)
	{
		vars->cmd_path = ft_strjoin(vars->my_paths[i], vars->cmd[0]);
		if (!vars->cmd_path)
			exit_on_error(vars);
		if (access(vars->cmd_path, F_OK) == 0)
			return (0);
		free(vars->cmd_path);
		i++;
	}
	write(2, "Error: command not found: ", 26);
	ft_putstr_fd(vars->cmd[0], 2);
	write(2, "\n", 1);
	exit(127);
}

static void	get_path(t_vars *vars)
{
	int	i;

	i = -1;
	while (vars->env[++i] != NULL)
	{
		if (ft_strncmp(vars->env[i], "PATH=", 5) == 0)
		{
			vars->my_paths = ft_split(&vars->env[i][5], ':');
			if (!vars->my_paths)
				exit_on_error(vars);
			break ;
		}
	}
}

/* Takes and handles input arguments and stores them in master struct. */
int	get_input(t_vars *vars, char **argv, char **envp, int h)
{
	int		i;
	char	*tmp;

	i = -1;
	vars->env = envp;
	get_path(vars);
	while (vars->my_paths[++i] != NULL)
	{
		tmp = vars->my_paths[i];
		vars->my_paths[i] = ft_strjoin(vars->my_paths[i], "/");
		if (!vars->my_paths)
			exit_on_error(vars);
		free(tmp);
	}
	if (h == 0)
		vars->input_file = argv[1];
	vars->output_file = argv[vars->cmd_count + 2 + h];
	vars->cmds_all = &argv[2 + h];
	return (0);
}
