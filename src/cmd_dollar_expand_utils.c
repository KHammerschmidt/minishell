#include "../header/minishell.h"

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

/* Iterates through cmd_line after $-expansion */
/* and cuts unexpanded envars if applicable    */
char	*cut_unused_envar(char *str)
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
		}
		if (str[i] == '\0')
			break ;
		if (str[i] == '$' && quote_type == 39)
			line = ft_strjoin_2(line, str, i);
		else if (str[i] == '$')
		{
			while (str[i] != ' ' && str[i] != '\0' && str[i] != quote_type)
				i++;
			continue ;
		}
		else
			line = ft_strjoin_2(line, str, i);
		i++;
	}
	return (line);
}