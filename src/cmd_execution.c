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

int	execute_cmd(t_vars *ms, char *cmd, char *args)
{
	char	**arg_str;

	arg_str = NULL;
	if (is_builtin(ms, cmd) == 0)
	{
		arg_str = ft_split(args, ' ');
		if (compare_str(cmd, "echo") == 0)
		{
			builtin_echo(ms, arg_str);
		}
		// if (compare_str(cmd, "cd") == 0)
		// 	builtin_cd(ms, ms->cmd->args);
		// if (compare_str(cmd, "env") == 0)
		// 	builtin_env(ms);
		// if (compare_str(cmd, "exit") == 0)
		// 	builtin_exit(ms);
		// if (compare_str(cmd, "export") == 0)
		// 	builtin_export(ms, );
		free(args);
	}
	else
	{
		// check if valid command, then execute or return error
	}
	return (0);
}
