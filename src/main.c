#include "../header/minishell.h"

/* Initialises main struct ms as well as builtin and env. */
int	init_struct(t_vars *ms, int argc, char **argv, char **envp)
{
	ms->argc = argc;
	ms->argv = argv;
	ms->fd_out = 1;						// Mio: for testing purposes only. 
	if (init_env(ms, envp) != 0)
		return (1);
	init_builtin(ms);
	// ms->lst = NULL;
	ms->lst = ft_calloc(1, sizeof(t_list));
	ms->cmd = NULL;
	ms->cmd = ft_calloc(1, sizeof(t_cmd));
	// ft_memset(&ms->cmd, 0, sizeof(t_cmd));
	// init_cmd(ms);												//necessary???

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
	int		i;

	i = 0;

	if (argc < 1 || argv[1])
		return (-1);
	// ft_memset(&ms, 0, sizeof(t_vars));
	ms = (t_vars) {0};
	init_struct(&ms, argc, argv, envp);
	while (1)
	{
		if (parsing(&ms) != 0)
			break ;
		// free(ms.cmd_line);
		i++;
		if (i == 5)
			break ;
	}
	// if (ms.cmd_line)
	// 	free(ms.cmd_line);
	// system("leaks minishell");
	return (0);
}
