#include "../header/minishell.h"

int	pipex(t_vars *ms)
{
	t_cmd	*current;
	pid_t	pid;

	current = ms->cmd;
	while (current != NULL)
	{
		if (pipe(ms->pipe_fd) == -1)	//protecten mio!
			printf("ERROR\n"); //ft_error_function
		if (is_builtin(ms, current->command[0]) == 1)
		{
			// input_redirection(current, ms);				//special case for builtin
			// output_redirection(current, ms);
			// execute_builtin(current->command, ms);
		}
		else
		{
			pid = fork();
			if (pid == 0)
			{
				input_redirection(current, ms);
				output_redirection(current, ms);
				execute_cmd(ms, current);
			}
			// close(ms->pipe_fd[1]);
			// close(ms->tmp_fd);
			if (ft_lstsize_cmd(ms->cmd) != 1)
			{
				// if (dup2(ms->pipe_fd[0], ms->tmp_fd) < 0)
				// 	perror("dup2 fd[0] into tmp_fd: ");
				// close(ms->pipe_fd[0]);
			}

			waitpid(pid, &ms->exit_status, 0);
			printf("exit status %d\n", ms->exit_status);
		}
		current = current->next;
	}
	return (WEXITSTATUS(ms->exit_status));
}

//wenn nur ein cmd ohne redirection (kein input output dup2)