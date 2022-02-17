#include "../header/minishell.h"

static char	*search_for_var(t_vars *ms, char *var)
{
	t_env	*current;

	current = ms->env;
	if (compare_str(var, "?") == 0)
		return (ft_itoa(ms->exit_status));
	while (current != NULL)
	{
		if (compare_str(current->name, var) == 0)
			return (current->content);
		current = current->next;
	}
	return (NULL);
}

static void	replicate_text(t_vars *ms, int *i, int *j)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_substr(ms->cmd_line, *j, *i - *j);
	if (ms->line == NULL)
		ms->line = ft_strdup(tmp);
	else
		ms->line = ft_strjoin(ms->line, tmp);
	free(tmp);
}

static void	add_expanded_var(t_vars *ms, int *i, int *j)
{
	char	*tmp;
	char	*var;

	tmp = NULL;
	var = NULL;
	var = ft_substr(ms->cmd_line, *j, *i - *j);
	tmp = ft_strdup(search_for_var(ms, var));
	if (tmp == NULL)
	{
		ms->line = ft_strjoin(ms->line, "$");
		ms->line = ft_strjoin(ms->line, var);
	}
	else
		ms->line = ft_strjoin(ms->line, tmp);
	*j = *i;
	free(var);
	free(tmp);
}

/* Checks if the dollar sign stands within double or single quotes
and returns the respective quote_type. */
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

/* Looks for $-signs and expands if respective variable is found in envar list. */
void	dollar_expansion(t_vars *ms)
{
	int		i;
	int		j;
	int		quote_on;
	int		quote_type;

	i = 0;
	j = 0;
	quote_on = 0;
	quote_type = 0;
	while (ms->cmd_line[i] != '\0')
	{
		quote_type = valid_dollar_sign(ms, i, &quote_on, quote_type);
		if (ms->cmd_line[i] == '$' && quote_type != 39)
		{
			replicate_text(ms, &i, &j);
			i++;
			j = i;
			while (ft_isalpha(ms->cmd_line[i]) == 1 || ms->cmd_line[i] == '?')
				i++;
			add_expanded_var(ms, &i, &j);
		}
		else
			i++;
	}
	replicate_text(ms, &i, &j);
}
