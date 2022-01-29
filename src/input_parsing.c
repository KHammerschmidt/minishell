#include "../header/minishell.h"

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

/* Function reads input with read_line() */
int	parsing(t_vars *ms)
{
	read_line(ms);
	if (create_cmd_table(ms) != 0)
		return (1);
	// save_commands(ms);
	print_cmd_lst(ms);
	return (0);
}
