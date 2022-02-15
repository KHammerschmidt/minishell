#include "../header/minishell.h"

/* Initialises main struct ms as well as builtin and env. */
int	init_struct(t_vars *ms, char **envp)
{
	if (init_env(ms, envp) != 0)
		return (1);
	init_builtin(ms);
	ms->cmd = ft_calloc(1, sizeof(t_cmd));				//Kathi: war auskommentiert?
	ms->cmd = NULL;
	ms->info = ft_calloc(1, sizeof(t_info));
	ft_memset(ms->info, 0, sizeof(t_info));
	return (0);
}

/* Reads user input and saves readline() in ms struct. */
int	read_line(t_vars *ms)
{
	char	*prompt;

	prompt = NULL;
	prompt = create_prompt(ms);
	if (ms->cmd_line)
		ft_free_string(ms->cmd_line);
	rl_init();
	if (prompt)
		ms->cmd_line = readline(prompt);
	else
		ms->cmd_line = readline("minishell ॐ  ");
	rl_reset();
	if (ms->cmd_line == NULL)							// (x) Makes CTRL+D work.
		exit(EXIT_SUCCESS);								// NOTE: replace exit() by own function incl. free() etc.
	if (ms->cmd_line && *ms->cmd_line)
		add_history (ms->cmd_line);
	free(prompt);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	ms;
	int		i;

	i = 0;
	if (argc < 1 || argv[1])
		return (-1);
	ms = (t_vars){0};
	init_struct(&ms, envp);
	while (1)
	{
		read_line(&ms);
		create_cmd_table(&ms);
		get_paths(&ms);

		// print_lst(&ms);
		// print_lst_last(&ms);

		// execute_cmd(&ms);

		free_cmd_struct(&ms);
		if (ms.line)
			ft_free_string(ms.line);
		reset_info_struct(ms.info);
		// system("leaks minishell");
	}
	return (0);
}
