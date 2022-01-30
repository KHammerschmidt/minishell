#include "../header/minishell.h"

int	is_builtin(t_vars *ms, char *cmd)
{
	t_list	*current;

	current = ms->builtins;
	while (current != NULL)
	{
		if (compare_str(current->content, cmd) == 0)
			return (0);
		current = current->next;
	}
	return (1);
}

int	execute_cmd(t_vars *ms)
{
	printf("MS1\n");
	printf("%s\n", ms->cmd->command[1]);
	printf("%d\n", ms->cmd->pipe);
	printf("MS33\n");
	if (is_builtin(ms, ms->cmd->command[0]) == 0)
	{
		if (compare_str(ms->cmd->command[0], "echo") == 0)
		{
			builtin_echo(ms);
		}
		// if (compare_str(cmd, "cd") == 0)
		// 	builtin_cd(ms, ms->cmd->args);
		// if (compare_str(cmd, "env") == 0)
		// 	builtin_env(ms);
		// if (compare_str(cmd, "exit") == 0)
		// 	builtin_exit(ms);
		// if (compare_str(cmd, "export") == 0)
		// 	builtin_export(ms, );
	}
	else
	{
		// check if valid command, then execute or return error
	}
	return (0);
}
