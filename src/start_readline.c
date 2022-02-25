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
	// ms->cmd_line = ft_strdup("echo \"hallo das ist ein test\"");
	rl_reset();
	if (ms->cmd_line == NULL)							// (x) Makes CTRL+D work.
		last_free(ms, 1);
	if (ms->cmd_line && *ms->cmd_line)
		add_history (ms->cmd_line);
	ft_free_string(&prompt);
	return (0);
}
