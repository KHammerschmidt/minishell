#include "../header/minishell.h"

int	pipex(t_vars *ms)
{
	t_cmd	*current;
	pid_t	pid;

	current = ms->cmd;
	input_redirection_1(current, ms);
	while (current != NULL)
	{
		if (pipe(ms->pipe_fd) == -1)	//protecten mio!
			printf("ERROR\n"); 			//ft_error_function
		if (current->pipe == 0 && is_builtin(ms, current->command[0]) == 1)
		{
			output_redirection(current, ms);					//extra function für builtin
			execute_builtin(ms, current);
			if (ms->pipe_fd[1] != STDOUT_FILENO)
				close(ms->pipe_fd[1]);
		}
		else
		{
			pid = fork();
			if (pid == 0)
			{
				if (is_builtin(ms, current->command[0]) == 1)
				{
					output_redirection(current, ms);					//extra function für builtin
					execute_builtin(ms, current);
					if (ms->pipe_fd[1] != STDOUT_FILENO)
						close(ms->pipe_fd[1]);
				}
				else
				{
					output_redirection(current, ms);
					execute_cmd(ms, current);
				}
			}
			close(ms->pipe_fd[1]);
			if (ms->tmp_fd != 0)
				close(ms->tmp_fd);
			if (dup2(ms->pipe_fd[0], ms->tmp_fd) < 0)
				// perror("dup2 tmp_fd: ");
			close(ms->pipe_fd[0]);
			waitpid(pid, &ms->exit_status, 0);
			input_redirection_2(current, ms);
			printf("%d\n", ms->exit_status);
		}
		current = current->next;
	}
	return (WEXITSTATUS(ms->exit_status));
}
