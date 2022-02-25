#include "../header/minishell.h"

/* Returns the position of character in a string or -1 if not found. */
int	ft_strchr_pos_red(char *s, char c, int i)
{
	if (s == NULL)
		return (-1);
	while (s[i] != (unsigned char)c && s[i] != '\0')
		i++;
	if (s[i] == (unsigned char)c)
		return (i);
	else
		return (-1);
}

/* Returns 1 if character is within quotes and 0 when it's not. */
int	valid_red(char *str, int pos)
{
	int	i;
	int	double_quote;
	int	single_quote;

	i = 0;
	double_quote = 0;
	single_quote = 0;
	while (i < pos)
	{
		if (str[i] == 34)
			double_quote++;
		if (str[i] == 39)
			single_quote++;
		i++;
	}
	if ((double_quote % 2) != 0 || (single_quote % 2) != 0)
		return (1);
	return (0);
}

/* Searches for redirections signs ('<' & '>') and saves information in t_info.
Sets the fd for input and output to standard value. */
void	lexer_parser_redirections(char **string, t_vars *ms)
{
	int		red_in;
	int		red_out;

	red_in = ft_strchr_pos(*string, '<');
	red_out = ft_strchr_pos(*string, '>');
	ms->info.fd_in = STDIN_FILENO;
	ms->info.fd_out = STDOUT_FILENO;
	ms->info.input_op = 0;
	ms->info.output_op = 0;
	if (red_in != -1)
		input_redirection(ms, string, red_in);
	if (red_out != -1)
		output_redirection(ms, string, red_out);
}
