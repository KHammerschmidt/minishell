#include "../header/minishell.h"

/* Function returns the end of the substring that should be created. */
int	ft_get_stop(char *str, int start)
{
	int	stop;
	int	within_quotes;
	int	quote;

	stop = start;															//continuing from the current postion in str
	quote = 0;
	within_quotes = 0;
	while (str[stop] != ' ' && str[stop] != '\0' && within_quotes == 0) 	//loop until next space if there is no quote yet
	{
		if (str[stop] == 34 && within_quotes == 0)							//if no quote is active & str[i] matched double quotes
			quote = 34;
		if (str[stop] == 39 && within_quotes == 0)							//if no quote is active & str[i] matched single quotes
			quote = 39;
		if (str[stop] == quote)												//if there is a quote increase quote counter and loop over the found quote
			within_quotes++;
		stop++;
	}
	while (within_quotes == 0 && str[stop] != ' ' && str[stop] != '\0')		//loop through str until next space
		stop++;
	while (within_quotes != 0 && str[stop] != '\0')							//while other matching quote has not been found loop through string
	{
		if (str[stop] == quote)												//if quote has been found, reset quote counter to 0
			within_quotes = 0;
		stop++;
	}
	while ((str[stop] != ' ' || str[stop] == quote) && str[stop] != '\0')	//while there is no space or quote loop through string
		stop++;
	return (stop);
}

/* Functions returns the start of the substring that is to be created. */
int	ft_get_start(char *str, int stop)
{
	int	start;

	start = stop;
	while (str[start] == ' ' && str[start] != '\0')							//loop over spaces at the beginning of str
		start++;
	return (start);
}

/* Cuts the quotes out of the string. */
char	*cut_quotes(char *str)
{
	int		i;
	int		quote_on;
	int		quote_type;
	char	*line;

	i = 0;
	quote_type = 0;
	quote_on = 0;
	line = ft_strdup("");
	printf("str: %s\n", str);
	while (str[i] != '\0')
	{
		if (str[i] == 34 && quote_on == 0)		//if no quote is active & str[i] matched double quotes
			quote_type = 34;
		if (str[i] == 39 && quote_on == 0)		//if no quote is active & str[i] matched single quotes
			quote_type = 39;
		if (str[i] == quote_type)				// check if quotes are active (quote_on > 0) increase quote_on to active quotes
		{
			if (quote_on == 1)
				quote_on = -1;
			quote_on++;
			i++;
		}
		// // line = ft_strnjoin(line, str[i++], 1);	//join the new character to line while overlooping the active quotes
		char *tmp2;
		tmp2 = ft_strdup(&str[i]);
		tmp2[1] = '\0';
		line = ft_strjoin(line,  tmp2);
		i++;
	}
	printf("line: %s\n", line);
	return (line);
}

char	*get_substring(int *start, int *stop, char *str)
{
	char	*tmp;

	tmp = NULL;
	*start = ft_get_start(str, *stop);
	*stop = ft_get_stop(str, *start);
	if (*start == *stop)
		return (NULL);
	tmp = ft_substr(str, *start, *stop - *start);
	return (tmp);
}

/* Split the input string by its spaces and groups together input in quotes. */
char	**ft_split_quotes(char *str)
{
	int		start;
	int		stop;
	char	**string;
	char	*tmp;
	int		k;

	stop = 0;
	start = 0;
	k = ft_count_substrings(str);										//count number of substrings for memory allocation
	// split = (char **)ft_calloc(sizeof(char *));
	string = (char **)ft_calloc(sizeof(char *), k + 1);
	printf("k: %d\n", k);
	// string = (char **)ft_calloc((sizeof(char *)), ft_strlen(str) + 1);
	if (string == NULL)
		printf("MEM ALLOC ERROR\n");//create exit function
	k = 0;
	// string = NULL;
	while (str[start] != '\0')
	{
		tmp = get_substring(&start, &stop, str);						//get start, stop of the temporary string
		printf("tmp: %s\n", tmp);
		if (tmp == NULL)
			break ;
		printf("HERE 1\n");
		if (ft_strchr(tmp, 34) != NULL || ft_strchr(tmp, 39) != NULL)	//if quotes are found in the string
		{
			printf("HERE 2\n");
			string[k++] = cut_quotes(tmp);								//split by quotes otherwise
		}
		else
		{
			printf("HERE 3\n");
			printf("tmp: %s\n", tmp);
			string[k++] = tmp;											//tmp has been splitted by spaces and becomes the command
		}
		printf("HERE 4\n");
		// free(tmp);
	}
	string[k] = 0;
	return (string);
}
