#include "../header/minishell.h"

/* Returns 1 for builtin and 0 when its no builtin. */
int	is_builtin(t_vars *ms, char *cmd)
{
	t_list	*current;

	current = ms->builtins;
	while (current != NULL)
	{
		if (compare_str(current->content, cmd) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

void	execute_builtin(t_vars *ms, t_cmd *current)
{
	if (compare_str(current->command[0], "echo") == 0)
		builtin_echo(ms, current);
	if (compare_str(current->command[0], "cd") == 0)
		builtin_cd(ms, current);
	if (compare_str(current->command[0], "pwd") == 0)
		builtin_pwd(ms, current);
	if (compare_str(current->command[0], "env") == 0)
		builtin_env(ms, current);
	if (compare_str(current->command[0], "export") == 0)
		builtin_export(ms, current);
	if (compare_str(current->command[0], "unset") == 0)
		builtin_unset(ms, current);
	if (compare_str(current->command[0], "exit") == 0)
		builtin_exit(ms, current);
}

void	execute_cmd(t_vars *ms, t_cmd *current)
{
	if (check_cmd(ms, current) == 0)
	{
		execve(current->execpath, current->command, ms->envp);
		close(ms->pipe_fd[1]);
		perror("Error");
		exit(EXIT_FAILURE);
	}
}
