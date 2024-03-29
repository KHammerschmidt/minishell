/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:17:23 by khammers          #+#    #+#             */
/*   Updated: 2022/03/15 20:23:54 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Intercepts SIGINT (CTRL+C) and SIGQUIT (CTRL+\) and prevents */
/*  minishell from quitting, prints empty new line instead.     */
static void	signal_handler2(int signum)
{
	if (signum == SIGINT || signum == SIGQUIT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
	}
	rl_redisplay();
}

/* Dups fd_out into STDOUT in case of an oufile redirection or into pipe. */
static void	ft_handle_stdout(t_cmd *current, t_vars *ms)
{
	if (current->output_op == -1 || current->output_op == -2)
	{
		if (dup2(current->fd_out, STDOUT_FILENO) < 0)
			perror("Error: dup2-oufile1: ");
		close(current->fd_out);
		close(ms->pipe_fd[1]);
	}
	else if (current->next == NULL)
		close(ms->pipe_fd[1]);
	else
	{
		if (dup2(ms->pipe_fd[1], STDOUT_FILENO) < 0)
			perror("error: dup2-outfile2: ");
		current->fd_out = dup(ms->pipe_fd[1]);
		close(ms->pipe_fd[1]);
	}
}

/* In case of infile redirection duplicates file fd into STDIN,
otherwise duplicates the tmp_fd (pipe_fd[[0]) into STDIN. */
static void	ft_handle_stdin(t_cmd *current, t_vars *ms)
{
	if (current->input_op == -1)
	{
		close(ms->pipe_fd[0]);
		if (dup2(current->fd_in, STDIN_FILENO) < 0)
			perror("Error: dup2-infile1: ");
		close(current->fd_in);
	}
	else if (current->input_op == 0 || current->input_op == -2)
	{
		close(ms->pipe_fd[0]);
		if (dup2(ms->tmp_fd, STDIN_FILENO) < 0)
			perror("Error: dup2-infile2: ");
		current->fd_in = dup(ms->tmp_fd);
		close(ms->tmp_fd);
	}
}

/* Opens up a pipe and forks process divided by child and parent process. */
void	ft_processes(t_vars *ms, t_cmd *current, pid_t *pid)
{
	if (pipe(ms->pipe_fd) == -1)
		printf("Error: ms->pipe_fd\n");
	else
	{
		*pid = fork();
		if (*pid < 0)
			printf("Error: process could not be forked\n");
		if (*pid == 0)
		{
			ft_handle_stdin(current, ms);
			ft_handle_stdout(current, ms);
			if (is_builtin(ms, current->command[0]) == 1)
				execute_builtin(ms, current);
			else
				execute_cmd(ms, current);
		}
		signal(SIGQUIT, signal_handler2);
		signal(SIGINT, signal_handler2);
		close(ms->pipe_fd[1]);
		close(ms->tmp_fd);
		if (dup2(ms->pipe_fd[0], ms->tmp_fd) < 0)
			perror("Error: dup2 fd[0] into tmp_fd: ");
		close(ms->pipe_fd[0]);
	}
}
