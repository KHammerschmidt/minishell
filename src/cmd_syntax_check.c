#include "../header/minishell.h"

/* Checks input for open quotes or multiple pipes. */
int	ft_syntax_check(char *str, t_vars *ms)
{
	int	i;

	i = 0;
	if (quote_status(str) == -1)
	{
		printf("Syntax error\n");
		ms->exit_status = 258;
		return (1);
	}
	while (str[i] != '\0')
	{
		if (str[i] == '|' && str[i + 1] == '|')
		{
			printf("Error: syntax error\n");
			ms->exit_status = 258;
			return (1);
		}
		i++;
	}
	return (0);
}
