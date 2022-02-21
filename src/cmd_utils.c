#include "../header/minishell.h"

/* Like ft_strjoin() but only appends one character at a time. */
char	*ft_strjoin_2(char *line, char *str, int i)
{
	char	*tmp;

	tmp = ft_strdup(&str[i]);
	tmp[1] = '\0';
	line = ft_strjoin(line, tmp);
	ft_free_string(tmp);
	return (line);
}

/* Counts amount of substrings by counting spaces except for when there are
quotes, then it counts the part in quotes as one substring. */
int	ft_count_substrings(char *str)
{
	int	i;
	int	counter;
	int	quote_on;
	int	quote;

	i = 0;
	quote = 0;
	counter = 0;
	quote_on = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == 34 && quote_on == 0) || (str[i] == 39 && quote_on == 0))
			quote = str[i];
		if (str[i] == ' ' && quote_on == 0)
			counter++;
		if (str[i] == quote)
			quote_on++;
		if (quote_on == 2)
			quote_on = 0;
		i++;
	}
	return (counter + 1);
}
