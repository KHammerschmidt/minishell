#include "../header/minishell.h"

/* Initialises main struct ms as well as builtin and env. */
int	init_struct(t_vars *ms, char **envp)
{
	// ms->fd_out = 1;							// Mio: for testing purposes only.
	if (init_env(ms, envp) != 0)
		return (1);
	init_builtin(ms);
	ms->cmd = ft_calloc(1, sizeof(t_cmd));
	ms->cmd = NULL;
	ms->info = ft_calloc(1, sizeof(t_info));
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	ms;

	t_cmd	*current;
	current = NULL;

	if (argc < 1 || argv[1])
		return (-1);
	ms = (t_vars){0};
	init_struct(&ms, envp);
	while (1)
	{
		if (parsing(&ms) != 0)
			break ;
		// read_line(&ms);						//KATHI: potential new structure instead of parsing().
		// create_cmd_table(&ms);

		// execute_cmd(&ms, current->command, current->args);
		// printf("cmd: %s   args: %s\n", current->next->command, current->next->args);
		// execute_cmd(&ms, current->command, current->args);
		// printf("MS00\n");
		// free(ms.cmd_line);
	// }
	// if (ms.cmd_line)
	// 	free(ms.cmd_line);
	// system("leaks minishell");
	}
	// current = ms.cmd;
	// int	i = 0;
	// while (current)
	// {
	// 	i = 0;
	// 	printf("New command\n");						// Mio: For testing purposes only.
	// 	while (current->command[i] != NULL)
	// 	{
	// 		printf("...%s...\n", current->command[i]);
	// 		i++;
	// 	}
	// 	current = current->next;
	// }
	return (0);
}


	//for printing
	// current = ms->cmd;
	// while (current != NULL)
	// {
	// 	i = 0;
	// 	printf("New command\n");						// Mio: For testing purposes only.
	// 	while (current->command[i] != NULL)
	// 	{
	// 		printf("%s\n", current->command[i]);
	// 		i++;
	// 	}
	// 	current = current->next;
	// }