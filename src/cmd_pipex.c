#include "../header/minishell.h"

int	pipex(t_vars *ms)
{
	t_cmd	*current;

	current = ms->cmd;
	while (current != NULL)
	{
		pipe(ms->pipe_fd);
		set_input();
		set_ouput();
		if (is_builtin(current->command[0]) == 1)
			execute_builtin(current->command);
		else
		{
			fork();
			if (child_process)
				execve(current->command);
			// wait(NULL);
			waitpid();
		}
		current = current->next;
	}
	// last_call();
}