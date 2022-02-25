#include "../header/minishell.h"

/* Frees:
- struct t_env (content & every element),
- builtin list t_list (content & element), */
void	last_free(t_vars *ms, int e_flag)
{
	free_t_env(&ms->env);			// ft_free_lst_env(&(*ms)->env);
	ft_free_strarray(&ms->envp);
	// free_env_list(ms);

	free_builtin_list(ms);
	// free_list(&(*ms)->builtins);
	ft_free_strarray(&ms->paths);

	// free_cmd_list(ms);
	// reset_info_struct(&ms.info);
	if (e_flag == 1)
		exit(ms->exit_status);
}

/* Initialises main struct ms, sets struct t_info to 0 and duplicates
the temporary fd into STDIN. */
static int	init_struct(t_vars *ms, char **envp)	// √
{
	if (init_env(ms, envp) != 0)
		return (1);
	init_builtin(ms);
	ms->tmp_fd = dup(STDIN_FILENO);
	ms->info = (t_info){0};
	return (0);
}

/* Resets the allocated memory and variables needed for the next input. */
void	reset(t_vars *ms)
{
	ft_free_strarray(&ms->paths);
	free_cmd_struct(ms);
	ft_free_string(&ms->line);
	if (ms->tmp_fd != STDIN_FILENO)
	{
		close(ms->tmp_fd);
		ms->tmp_fd = dup(STDIN_FILENO);
	}
}

int	main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv, char **envp)
{
	t_vars	ms;

	ms = (t_vars){0};
	if (init_struct(&ms, envp) != 0)				// √
		return (-1);
	while (1)
	{
		read_line(&ms);								// √
		if (compare_str(ms.cmd_line, "") == 0)
			continue ;
		// create_cmd_table(&ms);
		if (create_cmd_table(&ms) != 1)				// √
		{
			get_paths(&ms);
			ms.exit_status = pipex(&ms);
		}
		reset(&ms);
		system("leaks minishell");
	}
	last_free(&ms, 0);
	close(ms.tmp_fd);
	return (ms.exit_status);
}
