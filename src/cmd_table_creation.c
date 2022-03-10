#include "../header/minishell.h"

/* Sets the quote type (34 or 39) in case opening quote has been found and
closes the index respectively in the second call. If an immediate following
quote has been found, which means there is an empty double quote, all
variables are reset to 0 and the quote characters are jumped over. */
static int	set_quote_index(char *str, int *i, int *quote_type, int *quote_on)
{
	if (*quote_on == 0)
		*quote_type = str[*i];
	if (*quote_on == 1)
	{
		*quote_on = -1;
		*quote_type = 0;
	}
	(*quote_on)++;
	(*i)++;
	if (str[*i] == *quote_type)
	{
		(*i)++;
		*quote_on = 0;
		*quote_type = 0;
		if (str[*i] == '\0')
			return (1);
	}
	return (0);
}

/* When a quote is found the function sets the quote index of opening or 
closing quote. Simultaneously it is checked for empty quotes, which are then
cut out. Thereby char *temp is filled character for character. */
char	*cut_empty_quotes(t_vars *ms)
{
	int		i;
	char	*temp;
	int		quote_on;
	int		quote_type;

	i = 0;
	quote_on = 0;
	quote_type = 0;
	temp = ft_strdup("");
	while (ms->cmd_line[i] != '\0')
	{
		if ((ms->cmd_line[i] == quote_type)
			&& (ms->cmd_line[i + 1] == quote_type))
		{
			if (set_quote_index(ms->cmd_line, &i, &quote_type, &quote_on) == 1)
			{
				temp = ft_strjoin_2(temp, NULL, 1);
				break ;
			}
		}
		else
			temp = ft_strjoin_2(temp, ms->cmd_line, i);
		i++;
	}
	return (temp);
}

/* Checks the input string for syntax errors and expands any valid dollar
sign before cutting empty quotes of the input string. */
static int	input_preparation(t_vars *ms)
{
	char	*temp;

	temp = NULL;
	if (ft_syntax_check(ms->cmd_line, ms) != 0)
		return (1);
	if (ft_strchr_pos(ms->cmd_line, '$') != -1)
	{
		dollar_expansion(ms);
		if (ft_strchr_pos(ms->cmd_line, '$') != -1)
			ms->cmd_line = cut_unused_envar(ms->cmd_line);
	}
	temp = cut_empty_quotes(ms);
	ft_free_string(&ms->cmd_line);
	ms->cmd_line = ft_strdup(temp);
	ft_free_string(&temp);
	return (0);
}

/* Creates the simple command table, e.g. the char **command of struct t_cmd. */
int	create_cmd_table(t_vars *ms)
{
	char	*nxt_cmd_line;
	t_cmd	*new;

	new = NULL;
	nxt_cmd_line = NULL;
	if (input_preparation(ms) == 1)
		return (1);
	while (ms->cmd_line != NULL)
	{
		nxt_cmd_line = lexer_parser(ms);
		new = ft_lstnew_cmd(ms);
		ft_lstadd_back_cmd(&ms->cmd, new);
		if (nxt_cmd_line == NULL)
		{
			ft_free_string(&nxt_cmd_line);
			ft_free_string(&ms->cmd_line);
			break ;
		}
		ft_free_string(&ms->cmd_line);
		ms->cmd_line = ft_strdup(nxt_cmd_line);
		ft_free_string(&nxt_cmd_line);
	}
	return (0);
}
