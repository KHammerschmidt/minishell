#include "../header/minishell.h"

/* Indicates if the found quote is an opening (within_quotes == 0) or closing
(within_quotes == 1) quote and changes the status of the status. */
static int	check_quote_status(char *str, int stop, int *within_quotes, int quote)
{
	if (str[stop] == quote && (*within_quotes) == 0)
		(*within_quotes)++;
	else if (str[stop] == quote)
		(*within_quotes) = 0;
	return (*within_quotes);
}

/* Function returns the end of the substring that should be created.
It loops over the string until a quote (double or single quote) is found, then
sets the quote status and either loops over the string until the closing
quote is found and reverses the quote status or loops until a space is found and
returns that respective position. */
static int	stop_quotes(char *str, int start)
{
	int	stop;
	int	within_quotes;
	int	quote;

	stop = start;
	quote = 0;
	within_quotes = 0;
	while (str[stop] != ' ' && str[stop] != '\0' && within_quotes == 0)
	{
		if ((str[stop] == 34 && within_quotes == 0)|| (str[stop] == 39
			&& within_quotes == 0))
			quote = str[stop];
		check_quote_status(str, stop, &within_quotes, quote);
		stop++;
	}
	while (within_quotes == 0 && str[stop] != ' ' && str[stop] != '\0')
		stop++;
	while (within_quotes != 0 && str[stop] != '\0')
	{
		check_quote_status(str, stop, &within_quotes, quote);
		stop++;
	}
	while ((str[stop] != ' ' || str[stop] == quote) && str[stop] != '\0')
		stop++;
	return (stop);
}

/* Cuts the quotes out of the string. */
static char	*cut_quotes(char *str)
{
	int		i;
	int		quote_on;
	int		quote_type;
	char	*line;

	i = 0;
	quote_on = 0;
	quote_type = 0;
	line = ft_strdup("");
	while (str[i] != '\0')
	{
		if ((str[i] == 34 && quote_on == 0) || (str[i] == 39 && quote_on == 0))
			quote_type = str[i];
		if (str[i] == quote_type)
		{
			if (quote_on == 1)
				quote_on = -1;
			quote_on++;
			i++;
		}
		if (str[i] == '\0')
			break ;
		line = ft_strjoin_2(line, str, i);
		i++;
	}
	return (line);
}

/* Creates the temprary substring by determining the beginning and
ending of the word or respective string indicated by quotes. */
static char	*substring_quotes(int *start, int *stop, char *str)
{
	char	*tmp;

	tmp = NULL;
	*start = *stop;
	while (str[*start] == ' ' && str[*start] != '\0')
		(*start)++;
	*stop = stop_quotes(str, *start);
	if (*start == *stop)
		return (NULL);
	tmp = ft_substr(str, *start, *stop - *start);
	return (tmp);
}

/* Split the input string by its spaces and groups together input in quotes. */
char	**ft_split_quotes(char *str)
{
	int		k;
	int		start;
	int		stop;
	char	*tmp;
	char	**string;

	k = 0;
	stop = 0;
	start = 0;
	tmp = NULL;
	string = (char **)ft_calloc(sizeof(char *), ft_count_substrings(str) + 1);
	if (string == NULL)
		printf("Error\n");
	while (str[start] != '\0')
	{
		tmp = substring_quotes(&start, &stop, str);
		if (tmp == NULL)
			break ;
		// string[k] = ft_strdup(cut_quotes(tmp));					// Mio: ersetzt gegen Zeile drunter wegen Leaks
		string[k] = cut_quotes(tmp);
		// printf("string[k] = %s\n", string[k]);
		k++;
		ft_free_string(&tmp);
	}
	string[k] = NULL;
	return (string);
}
