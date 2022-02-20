#include "../header/minishell.h"

static int	ft_handle_stdout(t_cmd *current, t_vars *ms)
{
	if (current->next != NULL && current->pipe == 1)
	{
		if (dup2(ms->pipe_fd[1], STDOUT_FILENO) < 0)
			perror("dup2 outfile1: ");
		close(ms->pipe_fd[1]);
	}
	else
	{
		if (current->output_op == -1 || current->output_op == -2)
		{
			if (dup2(current->fd_out, STDOUT_FILENO) < 0)
				perror("dup2 oufile2: ");
			close(current->fd_out);
		}
		close(ms->pipe_fd[1]);
	}
	return (0);
}

static int	ft_handle_stdin(t_cmd *current, t_vars *ms)
{
	if (current->input_op == -1)
	{
		close(ms->pipe_fd[0]);
		if (dup2(current->fd_in, STDIN_FILENO) < 0)
			perror("dup2  infile1: ");
		close(current->fd_in);
	}
	else
	{
		close(ms->pipe_fd[0]);
		if (dup2(ms->tmp_fd, STDIN_FILENO) < 0)
			perror("dup2 infile2: ");
		close(ms->tmp_fd);
	}
	return (0);
}

int	pipex(t_vars *ms)
{
	t_cmd	*current;
	pid_t	pid;

	current = ms->cmd;
	while (current != NULL)
	{
		if (current->previous == NULL && current->next == NULL && is_builtin(ms, current->command[0]) == 1)
		{
			execute_builtin(ms, current);
			return (ms->exit_status);
		}
		if (pipe(ms->pipe_fd) == -1)
			printf("PIPE ERROR\n");
		pid = fork();
		if (pid < 0)
			printf("PID ERROR\n");
		if (pid == 0)
		{
			ft_handle_stdin(current, ms);
			ft_handle_stdout(current, ms);
			execute_cmd(ms, current);
		}
		// signal(SIGQUIT, SIG_IGN);
		// signal(SIGINT, SIG_IGN);
		close(ms->pipe_fd[1]);
		close(ms->tmp_fd);
		if (dup2(ms->pipe_fd[0], ms->tmp_fd) < 0)
			perror("dup2 fd[0] into tmp_fd: ");
		close(ms->pipe_fd[0]);
		current = current->next;
	}
	// close(ms->tmp_fd);
	waitpid(pid, &ms->exit_status, 0);
	return (WEXITSTATUS(ms->exit_status));
}