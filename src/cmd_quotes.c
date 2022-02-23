#include "../header/minishell.h"

/* Checks the quote status, returns (0) for no quotes, (1) for valid
quotes and (-1) for open quotes. */
int	check_quote_status(char *str)
{
	int	i;
	int	quote_on;
	int	quote_type;

	i = 0;
	quote_on = 0;
	quote_type = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == 34 || str[i] == 39) && quote_on == 0)
			quote_type = str[i];
		if (str[i] == quote_type)
		{
			if (quote_on == 1)
				quote_on = -1;
			quote_on++;
		}
		i++;
	}
	if (quote_on == 1)
		return (-1);
	if (quote_type == 0)
		return (0);
	return (1);
}
