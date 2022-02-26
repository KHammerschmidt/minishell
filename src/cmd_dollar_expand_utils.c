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

/* Iterates through cmd_line after $-expansion */
/* and cuts unexpanded envars if applicable    */
char	*cut_unused_envar(char *str)
{
	int		i;
	int		quote_on;
	int		quote_type;
	char	*line;
	int		quote_2;

	i = 0;
	quote_2 = 0;
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
			{
				quote_on = -1;
				quote_type = 0;
				quote_2 = 0;
			}
			quote_on++;
		}
		if (str[i] == '\0')
			break ;

		if (quote_type == 34 && str[i] == 39)
			quote_2 = str[i];
		if (str[i] == '$')
		{
			if (quote_type == 39)
			{
				while (str[i] != quote_type)
				{
					line = ft_strjoin_2(line, str, i);
					i++;
				}
				line = ft_strjoin_2(line, str, i);
			}
			if (quote_type == 34)
			{
				if (quote_2 == 39 && closed_single_quote_in_double_quote(str, i) == 0)
				{
					while (str[i] != quote_2)
					{
						if (str[i] == ' ')
							line = ft_strjoin_2(line, str, i);
						i++;
					}
					line = ft_strjoin_2(line, str, i);
				}
				else
				{
					while (str[i] != quote_type)
					{
						line = ft_strjoin_2(line, str, i);
						i++;
					}
				}
			}
			quote_type = 0;
			quote_on = 0;
		}
		else
			line = ft_strjoin_2(line, str, i);
		i++;
	}
	ft_free_string(&str);
	return (line);
}
