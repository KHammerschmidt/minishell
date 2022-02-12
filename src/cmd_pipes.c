#include "../header/minishell.h"

int	check_pipes_in_quote(t_vars *ms)			//Kathi: not finished
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (ms->cmd_line[i] != '|')
	{
		if (ms->cmd_line[i] == 34 || ms->cmd_line[i] == 39)
			flag++;
		i++;
	}
	return (i);
}

int	check_pipe_validity(char *str)
{
	int	i;
	int	double_quote;
	int	single_quote;

	i = 0;
	double_quote = 0;
	single_quote = 0;
	while (str[i] != '|')
	{
		if (str[i] == 34)			//double quote
			double_quote++;
		if (str[i] == 39)			//single quote
			single_quote++;
		// printf("str[i] %c\n", str[i]);
		i++;
	}
	if ((double_quote % 2) != 0 || (single_quote % 2) != 0)
		return (1);					//pipe is no valid pipe, it is in between quotes
	return (0);						//valid pipe
}
