#include "../header/minishell.h"

/* Function returns the end of the substring that should be created. */
static int	get_stop(char *str, int start)
{
	int	stop;
	int	within_quotes;
	int	quote;

	stop = start;
	quote = 0;
	within_quotes = 0;
	while (str[stop] != ' ' && str[stop] != '\0' && within_quotes == 0)
	{
		if ((str[stop] == 34 && within_quotes == 0) || (str[stop] == 39
				&& within_quotes == 0))
			quote = str[stop];
		check_open_closed_quote(str, stop, &within_quotes, quote);
		stop++;
	}
	while (within_quotes == 0 && str[stop] != ' ' && str[stop] != '\0')
		stop++;
	while (within_quotes != 0 && str[stop] != '\0')
	{
		check_open_closed_quote(str, stop, &within_quotes, quote);
		stop++;
	}
	while ((str[stop] != ' ' || str[stop] == quote) && str[stop] != '\0')
		stop++;
	return (stop);
}

/* Sets the quote type (34 or 39) in case opening quote has been found and
closes the index respectively in the second call. */
static void	set_quote_index(char *str, int *i, int *quote_type, int *quote_on)
{
	if (*quote_on == 0)
		*quote_type = str[*i];
	if (str[*i] == *quote_type)
	{
		if (*quote_on == 1)
			*quote_on = -1;
		(*quote_on)++;
		(*i)++;
	}
}

/* Cuts the quotes out of the string. */
char	*cut_quotes(char *str)
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
		if (str[i] == 34 || str[i] == 39)
			set_quote_index(str, &i, &quote_type, &quote_on);
		if (str[i] == '\0')
			break ;
		line = ft_strjoin_2(line, str, i);
		i++;
	}
	return (line);
}

/* Creates a substring by determining the beginning and end of a word
or string within quotes. */
static char	*get_substring(int *start, int *stop, char *str)
{
	char	*tmp;

	tmp = NULL;
	*start = *stop;
	while (str[*start] == ' ' && str[*start] != '\0')
		(*start)++;
	*stop = get_stop(str, *start);
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
		tmp = get_substring(&start, &stop, str);
		if (tmp == NULL)
			break ;
		string[k] = cut_quotes(tmp);
		k++;
		ft_free_string(&tmp);
	}
	string[k] = NULL;
	return (string);
}
