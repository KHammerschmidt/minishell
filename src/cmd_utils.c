#include "../header/minishell.h"

/* Like ft_strjoin() but only appends one character at a time. */
char *ft_strjoin_2(char *line, char *str, int i)
{
	char *tmp;

	tmp = ft_strdup(&str[i]);
	tmp[1] = '\0';
	line = ft_strjoin(line, tmp);
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



// char	*copy_str_without_quotes(char *str)			 //INFO: $sign has to work
// {
// 	char	*tmp;
// 	char	*argument;

// 	tmp = "\"\\";
// 	argument = ft_strtrim(str, tmp);				//if no command -> access wirft command not found aus!
// 	return (argument);
// }

// /* Initialises the variables of t_cmd, allocates memory for the
// **command variable as the size of size + 1. */
// void	init_cmd(t_cmd *node, int size, char **arr)
// {
// 	node->op = 0;
// 	node->pipe = 0;
// 	node->command = NULL;
// 	// node->command = ft_calloc(sizeof(*(node->command)), size + 1);
// 	// if (!node->command)
// 	// 	return ;										//Fehler einbauen!
// 	node->command = arr;
// 	node->outfile = NULL;
// 	node->infile = NULL;
// 	node->errfile = NULL;
// 	node->next = NULL;
// 	if (!size)
// 		printf("\n");
// }

/* Counts the characters of a string for memory allocation, every character
except for quotes it being counted. */
// int	ft_count_chars(char *str, t_vars *ms)
// {
// 	int	i;
// 	int	counter;

// 	i = 0;
// 	counter = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (ms->info->double_quote_counter == 1 && str[i] != 34)
// 			counter++;
// 		if (ms->info->single_quote_counter == 1 && str[i] != 39)
// 			counter++;
// 		i++;
// 	}
// 	return (counter);
// }