/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mio <mio@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:48:24 by khammers          #+#    #+#             */
/*   Updated: 2022/03/10 13:22:38 by mio              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

// #include <sys/wait.h>				// Mio: activate for use with VALGRIND

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
			perror("dup2 oufile1: ");
		close(current->fd_out);
		close(ms->pipe_fd[1]);
	}
	else if (current->next == NULL)
		close(ms->pipe_fd[1]);
	else
	{
		if (dup2(ms->pipe_fd[1], STDOUT_FILENO) < 0)
			perror("dup2 outfile2: ");
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
			perror("dup2  infile1: ");
		close(current->fd_in);
	}
	else if (current->input_op == 0 || current->input_op == -2)
	{
		close(ms->pipe_fd[0]);
		if (dup2(ms->tmp_fd, STDIN_FILENO) < 0)
			perror("dup2 infile2: ");
		current->fd_in = dup(ms->tmp_fd);
		close(ms->tmp_fd);
	}
}

/* Opens up a pipe and forks process divided by child and parent process. */
static void	ft_processes(t_vars *ms, t_cmd *current, pid_t *pid)
{
	if (pipe(ms->pipe_fd) == -1)
		printf("PIPE ERROR\n");
	else
	{
		*pid = fork();
		if (*pid < 0)
			printf("PID ERROR\n");
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
			perror("dup2 fd[0] into tmp_fd: ");
		close(ms->pipe_fd[0]);
	}
}

int	ft_waiting(pid_t *pid, int *save)
{
	int	i;

	i = 0;
	i = waitpid(0, save, 0);
	if (i == *pid)
	{
		return (0);
	}
	else
		return (-1);
}

int	builtin_check(t_vars *ms, t_cmd *current)
{
	if (current->next == NULL && current->previous == NULL
	&& is_builtin(ms, current->command[0]) == 1)
		return (0);
	return (1);
}

		// {									//Kathi: Frage was soll passieren wenn command == NULL?
		// 	if (current->next == NULL)
		// 		return (0);
		// 	else
		// 		current = current->next;
		// 	continue;

/* Checks if input is only a builtin, if yes executes the builtin in the parent
otherwise calls ft_proceses() to introduce child and parent process. Waiting
for any children, indicated by pid == -1. */
int	pipex(t_vars *ms)
{
	int		save;
	pid_t	pid;
	t_cmd	*current;

	pid = 0;
	save = 0;
	current = ms->cmd;
	while (current != NULL)
	{
		if (current->command == NULL && current->next == NULL)
			return (0);
		else if (current->flag == -1)
		{
			ms->exit_status = 1;
			if (current->next == NULL)
				return (ms->exit_status);
		}
		else if (builtin_check(ms, current) == 0)
			return (ft_builtin_parent(current, ms));
		else
			ft_processes(ms, current, &pid);
		current = current->next;
	}
	while (ft_waiting(&pid, &save) == -1)
		ms->exit_status = save;
	ms->exit_status = save;
	return (WEXITSTATUS(ms->exit_status));
}

// 	while (ft_waiting != -1)
// 	while (i != -1)
// 	{
// 		i = waitpid(0, &save, 0);
// 		if (i == pid)
// 			ms->exit_status = save;
// 	}
// 	return (WEXITSTATUS(ms->exit_status));
// }

	//  && current->next == NULL)
	// 		return (1);
	// 	else if (current->flag == -1)
	// 		ms->exit_status = 1;
	// 	{
	// 		// ms->exit_status = 1;
	// 		// if (current->next == NULL)
	// 		// 	return (ms->exit_status);
	// 	}

	// 	 b