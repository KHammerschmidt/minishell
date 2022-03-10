#include "../header/minishell.h"

int	closed_single_quote_in_double_quote(char *str, int i)
{
	int	pos_single;
	int	pos_double;

	pos_single = ft_strchr_pos(&str[i], 39);
	pos_double = ft_strchr_pos(&str[i], 34);
	if (pos_single < pos_double && pos_single != -1)
		return (0);
	return (1);
}

static void	set_quote_flags(char c, int *quote_on, int *quote_type, \
		int *quote_2)
{
	if ((c == 34 && *quote_on == 0) || (c == 39 && *quote_on == 0))
		*quote_type = c;
	if (c == *quote_type)
	{
		if (*quote_on == 1)
		{
			*quote_on = -1;
			*quote_type = 0;
			*quote_2 = 0;
		}
		(*quote_on)++;
	}
}

static void	init_quote_struct(t_quotes *qt)
{
	qt->i = 0;
	qt->quote_2 = 0;
	qt->quote_on = 0;
	qt->quote_type = 0;
	qt->line = ft_strdup("");
}

/* Iterates through cmd_line after $-expansion */
/* and cuts unexpanded envars if applicable    */
char	*cut_unused_envar(char *str)
{
	t_quotes	qt;

	init_quote_struct(&qt);
	while (str[qt.i] != '\0')
	{
		set_quote_flags(str[qt.i], &qt.quote_on, &qt.quote_type, &qt.quote_2);
		if (qt.quote_type == 34 && str[qt.i] == 39)
			qt.quote_2 = str[qt.i];
		handle_dsign(&qt, str);
	}
	ft_free_string(&str);
	return (qt.line);
}

/* Checks if the dollar sign stands within double or single quotes
and returns the respective quote_type. Returns 0 when no quotes. */
int	valid_dollar_sign(t_vars *ms, int i, int *quote_on, int quote_type)
{
	if (ms->cmd_line[i] == 34 || ms->cmd_line[i] == 39)
	{
		if (*quote_on == 0)
			quote_type = ms->cmd_line[i];
		if (*quote_on == 1 && ms->cmd_line[i] == quote_type)
		{
			*quote_on = -1;
			quote_type = 0;
		}
		(*quote_on)++;
	}
	return (quote_type);
}
