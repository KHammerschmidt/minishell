#include "../header/minishell.h"

/* Cuts empty quotes when necessary. */
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
		if (ms->cmd_line[i] == 34 || ms->cmd_line[i] == 39)
		{
			if (quote_on == 0)
				quote_type = ms->cmd_line[i];
			if (quote_on == 1 && ms->cmd_line[i] == quote_type)
			{
				quote_on = -1;
				quote_type = 0;
			}
			(quote_on)++;
		}
		if ((ms->cmd_line[i] == quote_type) \
			&& (ms->cmd_line[i + 1] == quote_type))
		{
			i++;
			if (ms->cmd_line[i] == '\0')
			{
				temp = ft_strjoin_2(temp, NULL, 1);
				break ;
			}
		}
		else
			temp = ft_strjoin_2(temp, ms->cmd_line, i);
		i++;
	}
	ft_free_string(&ms->cmd_line);
	return (temp);
}

/* Creates the simple command table, e.g. the char **command of struct t_cmd. */
int	create_cmd_table(t_vars *ms)
{
	char	*nxt_cmd_line;
	t_cmd	*new;

	new = NULL;
	nxt_cmd_line = NULL;
	if (ft_syntax_check(ms->cmd_line, ms) != 0)
		return (1);
	if (ft_strchr_pos(ms->cmd_line, '$') != -1)
	{
		dollar_expansion(ms);
		if (ft_strchr_pos(ms->cmd_line, '$') != -1)
			ms->cmd_line = cut_unused_envar(ms->cmd_line);
	}
	ms->cmd_line = cut_empty_quotes(ms);
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
