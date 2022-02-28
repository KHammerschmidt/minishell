#include "../header/minishell.h"

/* Initialises main struct ms, sets struct t_info to 0 and duplicates
the temporary fd into STDIN. */
int	init_struct(t_vars *ms, char **envp)
{
	if (init_env(ms, envp) != 0)
		return (1);
	init_builtin(ms);
	ms->tmp_fd = dup(STDIN_FILENO);
	ms->info = (t_info){0};
	return (0);
}

int	main(__attribute__((unused)) int argc, __attribute__((unused))
	char **argv, char **envp)
{
	t_vars	ms;

	ms = (t_vars){0};
	if (init_struct(&ms, envp) != 0)
		return (-1);
	while (1)
	{
		read_line(&ms);
		if (compare_str(ms.cmd_line, "") == 0)
			continue ;
		if (create_cmd_table(&ms) == 0)
		{
			get_paths(&ms);
			ms.exit_status = pipex(&ms);
		}
		reset(&ms);
		// system("leaks minishell > OUTFILE");
	}
	last_free(&ms, 0);
	close(ms.tmp_fd);
	return (ms.exit_status);
}
