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
	ft_memset(ms->info, 0, sizeof(t_info));
	// ms->info = &(t_info){NULL, NULL, NULL, NULL, 0, 0, 0, 0, 0, 0};
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
		read_line(&ms);
		create_cmd_table(&ms);
		reset_info_struct(ms.info);
		// execute_cmd(&ms, current->command, current->args);
		// printf("cmd: %s   args: %s\n", current->next->command, current->next->args);
		// execute_cmd(&ms, current->command, current->args);
		// printf("MS00\n");
		// free(ms.cmd_line);
	// }
		// system("leaks minishell");
	}
	return (0);
}


		// current = ms.cmd;
		// int	i = 0;
		// while (current && current->command != NULL)
		// {
		// 	i = 0;
		// 	printf("New command\n");						// Mio: For testing purposes only.
		// 	while (current->command[i] != NULL)
		// 	{
		// 		printf("...%s...\n", current->command[i]);
		// 		i++;
		// 	}
		// 		current = current->next;
		// }
		// while (current != NULL)								// Mio: Delete command table after each execution.
		// {
		// 	ft_free_strarray(current->command);				// Mio: Replace by function to empty and free the complete list
		// 	current = current->next;
		// }
		// ms.cmd = NULL;					// Mio: Leaks?!
		// 	print_cmd_lst(ms);