#include "../header/minishell.h"

/* Reads user input and saves readline() in ms struct. */
int	read_line(t_vars *ms)
{
	char	*prompt;

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
	ft_free_string(&prompt);
	return (0);
}