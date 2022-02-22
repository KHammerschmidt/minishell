#include "../header/minishell.h"

/* Frees:
- struct t_env (content & every element),
- builtin list t_list (content & element), */
void	last_free(t_vars *ms)
{
	free_t_env(&ms->env);			// ft_free_lst_env(&(*ms)->env);
	ft_free_strarray(ms->envp);
	// free_env_list(ms);

	free_builtin_list(ms);
	// free_list(&(*ms)->builtins);
	ft_free_strarray(ms->paths);

	// free_cmd_list(ms);
	// reset_info_struct(&ms.info);
}

/* Initialises main struct ms as well as builtin and env. */
static int	init_struct(t_vars *ms, char **envp)	// √
{
	if (init_env(ms, envp) != 0)
		return (1);
	init_builtin(ms);
	ms->tmp_fd = dup(STDIN_FILENO);
	ms->info = (t_info){0};
	get_paths(ms);
	return (0);
}

int	main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv, char **envp)
{
	t_vars	ms;
	int		i;

	i = 0;
	ms = (t_vars){0};
	if (init_struct(&ms, envp) != 0)				// √
		return (-1);
	while (1)
	{
		read_line(&ms);								// √
		create_cmd_table(&ms);						// open
		ms.exit_status = pipex(&ms);
		free_cmd_struct(&ms);						//double free error bei i == 1
		if (ms.line)
		{
			free(ms.line);
			ms.line = NULL;
		}
		if (i == 1)
		{
			break ;
		// exit(ms.exit_status);
		}
		i++;
	}
	last_free(&ms);
	close(ms.tmp_fd);
	system("leaks minishell");
	return (ms.exit_status);
}
