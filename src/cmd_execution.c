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
	printf("MS1\n");
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

// int	main(int argc, char **argv, char **envp)
// {
// 	t_vars	ms;
// 	t_cmd	*current;
// 	int		i;

// 	i = 0;

// 	if (argc < 1 || argv[1])
// 		return (-1);
// 	// ft_memset(&ms, 0, sizeof(t_vars));
// 	ms = (t_vars) {0};
// 	init_struct(&ms, argc, argv, envp);
// 	current = ms.cmd;
// 	while (1)
// 	{
// 		if (parsing(&ms) != 0)
// 			break ;
// 		printf("cmd: %s   args: %s\n", current->next->command, current->next->args);
// 		execute_cmd(&ms, current->command, current->args);
// 		printf("MS00\n");
// 		// free(ms.cmd_line);
// 	}
// 	// if (ms.cmd_line)
// 	// 	free(ms.cmd_line);
// 	// system("leaks minishell");
// 	return (0);
// }
