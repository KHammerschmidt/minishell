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

int	execute_cmd(t_vars *ms)
{
	t_cmd	*current;

	current = ms->cmd;
	if (is_builtin(ms, ms->cmd->command[0]) == 1)
	{
		if (compare_str(ms->cmd->command[0], "echo") == 0)
			builtin_echo(ms);
		if (compare_str(ms->cmd->command[0], "cd") == 0)
			builtin_cd(ms);
		if (compare_str(ms->cmd->command[0], "pwd") == 0)
			builtin_pwd(ms);
		if (compare_str(ms->cmd->command[0], "env") == 0)
			builtin_env(ms);
		if (compare_str(ms->cmd->command[0], "export") == 0)
			builtin_export(ms);
		if (compare_str(ms->cmd->command[0], "unset") == 0)
			builtin_unset(ms);
		if (compare_str(ms->cmd->command[0], "exit") == 0)
			builtin_exit(ms);
	}
	else
	{

		// check_cmd(ms, ms->cmd->command[0]);
		// check if valid ms->cmd->command, then execute or return error
	}
	return (0);
}
