#include "../header/minishell.h"

char	**copy_strarray(char **strarray)
{
	char	**ret;
	int		i;

	i = 0;
	while (strarray[i] != NULL)
		i++;
	ret = (char **)malloc((i + 1) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (strarray[i] != NULL)
	{
		ret[i] = ft_strdup(strarray[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

/* Initialises main struct ms as well as builtin and env. */
int	init_struct(t_vars *ms, char **envp)
{
	// ms->env = NULL;											// ditto: warum muss das NULL gesetzt werden?
	if (init_env(ms, envp) != 0)
		return (1);
	// ms->builtins = NULL;
	init_builtin(ms);
	// ms->cmd = ft_calloc(1, sizeof(t_cmd));				// Kathi: war auskommentiert? Mio: Brauchen wir das wirklich?! Scheint auch ohne zu gehen. Warum?
	// ms->cmd = NULL;											// Warum muessen wir alles auf NULL setzen? Dachte, das machen wir in der main mit ms = (t_vars){0};? Scheint aber wichtig zu sein, weil sonst komische Fehler.
	ms->envp = copy_strarray(envp);
	// ms->info = ft_calloc(1, sizeof(t_info));				// Warum brauchen wir das hier? Gibt sonst segfault. Ich muss dieses ganze mem-alloc Thema unbedingt noch verstehen.
	// ms->info = malloc(sizeof(t_info));
	// ms->exit_status = 0;
	ms->tmp_fd = dup(STDIN_FILENO);
	ms->info = (t_info){0};
	return (0);
}

/* Reads user input and saves readline() in ms struct. */
int	read_line(t_vars *ms)
{
	char	*prompt;

	prompt = NULL;
	prompt = create_prompt(ms);
	if (ms->cmd_line)
		ft_free_string(&ms->cmd_line);
	rl_init();
	if (prompt)
		ms->cmd_line = readline(prompt);
	else
		ms->cmd_line = readline("minishell ॐ  ");
	rl_reset();
	if (ms->cmd_line == NULL)							// (x) Makes CTRL+D work.
		free_and_exit(ms, 1, 0);
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
		ms.exit_status = pipex(&ms);
		if (i == 2)
			exit(ms.exit_status);
		free_cmd_struct(&ms);
		if (ms.line)
		{
			free(ms.line);
			ms.line = NULL;
		}
		reset_info_struct(&ms.info);
		i++;
	}
	return (ms.exit_status);
}
