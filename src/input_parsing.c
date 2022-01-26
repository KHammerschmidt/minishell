#include "../header/minishell.h"

/* Reads user input and saves readline() in ms struct. */
int	read_line(t_vars *ms)
{
	// char	*tmp;					// necessary?
	char	*prompt;

	// tmp = readline("");				// necessary?
	// if (tmp == NULL)											//(end of input file)
	// {
	// 	printf("End of input file\n");
	// 	return (1);
	// }
	// ms->cmd_line = ft_calloc(sizeof(char), ft_strlen(tmp));	// do we need to allocate mem? readline() does that.
	// if (!ms->cmd_line)
	// {
	// 	printf("Error: Memory allocation failed\n");
	// 	return (1);
	// }
	// ms->cmd_line = ft_strdup(tmp);
	// free(tmp);

	prompt = NULL;
	prompt = create_prompt(ms);
	if (ms->cmd_line)
	{
		free (ms->cmd_line);
		ms->cmd_line = NULL;
	}
	rl_init();
	if (prompt)
		ms->cmd_line = readline(prompt);
	else
		ms->cmd_line = readline("minishell ॐ  ");
	rl_reset();
	if (ms->cmd_line == NULL)						// (x) Makes CTRL+D work.
		exit(EXIT_SUCCESS);							// NOTE: replace exit() by own function incl. free() etc.
	if (ms->cmd_line && *ms->cmd_line)
		add_history (ms->cmd_line);
	free(prompt);
	return (0);
}

/* Function reads input with read_line()
PROMPT HAS TO BE ADDED */
int	parsing(t_vars *ms)
{
	// int		i;

	// i = 0;
	// while (i == 0)
	// {
	// 	if (read_line(ms) != 0)
	// 		return (1);
	// 	i++;
	// }
	read_line(ms);
	if (create_cmd_table(ms) != 0)
		return (1);
	print_lst(ms);
	return (0);
}
