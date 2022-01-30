#include "../header/minishell.h"

/* Initialises main struct ms as well as builtin and env. */
int	init_struct(t_vars *ms, int argc, char **argv, char **envp)
{
	ms->argc = argc;
	ms->argv = argv;
	if (init_env(ms, envp) != 0)
		return (1);
	init_builtin(ms);
	ms->lst = NULL;
	ms->lst = ft_calloc(1, sizeof(t_list));
	ms->input = NULL;
	ms->input = ft_calloc(1, sizeof(t_input));
	ms->cmd = NULL;													// (loeschen!!!)
	// ms->cmd = ft_calloc(1, sizeof(t_cmd));
	// ft_memset(&ms->cmd, 0, sizeof(t_cmd));						//necessary???

	// ms->input = ft_calloc(1, sizeof(t_input));
	// if (!ms->input)
	// 	return (-1);
	// ms->arr = ft_calloc(sizeof(char *), 8);
	// if (ms->arr == NULL)
	// {
	// 	printf("Error\n");
	// 	return (1);
	// }
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	ms;
	t_cmd	*current;
	int		i;

	i = 0;

	if (argc < 1 || argv[1])
		return (-1);
	// current = NULL;
	ms = (t_vars){0};
	init_struct(&ms, argc, argv, envp);
	while (1)
	{
		if (parsing(&ms) != 0)
			break ;
		// while (ms.cmd->command[i])
		// {
		// 	printf("%s 		", ms.cmd->command[i]);
		// 	i++;
		// }
		// printf("\n");
		// // current = ms.cmd;
		// execute_cmd(&ms/* , current->command */);
		// free(ms.cmd_line);
		current = ms.cmd;
		while (current != NULL)
		{
			i = 0;
			printf("New command\n");						// Mio: For testing purposes only.
			while (current->command[i] != NULL)
			{
				printf("%s\n", current->command[i]);
				i++;
			}
			current = current->next;
		}
	}
	// if (ms.cmd_line)
	// 	free(ms.cmd_line);
	system("leaks minishell > leaks.txt");
	return (0);
}
