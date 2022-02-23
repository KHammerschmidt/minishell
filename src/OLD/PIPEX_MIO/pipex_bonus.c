/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 12:28:00 by mortmeie          #+#    #+#             */
/*   Updated: 2021/11/19 16:48:47 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

/* Gets next command's string and executes the command. */
static void	execute(t_vars *vars)
{
	vars->cmd = ft_split(vars->cmds_all[vars->i], ' ');
	if (check_cmd(vars) == 0)
	{
		execve(vars->cmd_path, vars->cmd, vars->env);
		close(vars->pipe[1]);
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

/* Swaps parent's STDIN with pipe[0], return error if fails. */
static void	parent_process(t_vars *vars)
{
	close(vars->pipe[1]);
	if (dup2(vars->pipe[0], STDIN_FILENO) < 0)
		exit_on_error(vars);
	close(vars->pipe[0]);
}

/* Swaps child's STDOUT with pipe[1], calls execute function or */
/* stdin_to_pipe() on first call if here_doc is present.        */
static void	child_process(t_vars *vars, int h)
{
	close(vars->pipe[0]);
	if (dup2(vars->pipe[1], STDOUT_FILENO) < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	close(vars->pipe[1]);
	if (h == 1)
		stdin_to_pipe(vars);
	else
		execute(vars);
}

/* Last execution without prior opening of a new pipe, */
/* using parent's STDOUT (set to outfile). Stores last */
/* command's exit status to vars->exit_code.           */
void	last_call(t_vars *vars)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		execute(vars);
	else
		waitpid(pid, &vars->exit_code, 0);
}

/* Opens pipe and forks process. Calls parent_process(). */
/* Calls child_process().                                */
int	pipex(t_vars *vars, int h)
{
	pid_t	parent;

	if (pipe(vars->pipe) == -1)
		exit_on_error(vars);
	parent = fork();
	if (parent < 0)
		exit_on_error(vars);
	if (parent)
		parent_process(vars);
	else
		child_process(vars, h);
	close(vars->pipe[0]);
	close(vars->pipe[1]);
	return (0);
}
