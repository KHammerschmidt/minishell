#include "../header/minishell.h"

// #include <sys/wait.h>				// Mio: activate for use with VALGRIND

/* Duplicates fd_out into STDOUT in case of an oufile redirection,
otherwise into the pipe. */
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

/* Duplicates fd_in into STDIN in case of an infile redirection, otherwise
into the pipe. If a here_doc is found is opens it and reads it until the limiter
has been found. */
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

int	pipex(t_vars *ms)
{
	t_cmd	*current;
	pid_t	pid;

	current = ms->cmd;
	while (current != NULL)
	{
		if (current->next == NULL && current->previous == NULL
			&& is_builtin(ms, current->command[0]) == 1)			//hier kann er nicht drauf zugreifen
			{
				ft_builtin_parent(current, ms);
				return (ms->exit_status);					// Mio: Added this line to prevent function to jump to waitpid() at the bottom, where ms->exit_status was uninitialised according to VALGRIND (don't know why it's not in this case)
			}
		else
		{
			if (pipe(ms->pipe_fd) == -1)
				printf("PIPE ERROR\n");
			else
			{
				pid = fork();
				if (pid < 0)
					printf("PID ERROR\n");
				if (pid == 0)
				{
					ft_handle_stdin(current, ms);
					ft_handle_stdout(current, ms);
					if (is_builtin(ms, current->command[0]) == 1)
						execute_builtin(ms, current);
					else
						execute_cmd(ms, current);
				}
				close(ms->pipe_fd[1]);
				close(ms->tmp_fd);
				if (dup2(ms->pipe_fd[0], ms->tmp_fd) < 0)
					perror("dup2 fd[0] into tmp_fd: ");
				close(ms->pipe_fd[0]);
			}
		}
		// signal(SIGQUIT, SIG_IGN);
		// signal(SIGINT, SIG_IGN);
		current = current->next;
	}
	waitpid(pid, &ms->exit_status, 0);
	return (WEXITSTATUS(ms->exit_status));
}