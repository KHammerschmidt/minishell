#include "../header/minishell.h"

/* Reads user input and saves readline() in ms struct. */
int	read_line(t_vars *ms)
{
	char	*tmp;

	tmp = readline("");
	if (tmp == NULL)											//(end of input file)
	{
		printf("End of input file\n");
		return (1);
	}
	ms->cmd_line = ft_calloc(sizeof(char), ft_strlen(tmp));
	if (!ms->cmd_line)
	{
		printf("Error: Memory allocation failed\n");
		return (1);
	}
	ms->cmd_line = ft_strdup(tmp);
	free(tmp);
	return (0);
}

/* Function reads input with read_line()
PROMPT HAS TO BE ADDED */
int	parsing(t_vars *ms)
{
	int		i;

	i = 0;
	while (i == 0)
	{
		if (read_line(ms) != 0)
			return (1);
		i++;
	}
	if (create_cmd_table(ms) != 0)
		return (1);
	print_lst(ms);
	return (0);
}
