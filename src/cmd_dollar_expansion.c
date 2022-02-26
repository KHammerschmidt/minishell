#include "../header/minishell.h"

static char	*search_for_var(t_vars *ms, char *var)
{
	t_env	*current;
	char	*tmp;

	tmp = NULL;
	current = ms->env;
	if (compare_str(var, "?") == 0)
	{
		tmp = ft_itoa(ms->exit_status);
		return (tmp);
	}
	while (current != NULL)
	{
		if (compare_str(current->name, var) == 0)
			return (ft_strdup(current->content));
		current = current->next;
	}
	return (NULL);
}

static void	add_expanded_var(t_vars *ms, int *i, int *j)
{
	char	*tmp;
	char	*var;

	var = ft_substr(ms->cmd_line, *j, *i - *j);
	tmp = search_for_var(ms, var);
	if (tmp == NULL)
	{
		if (ms->line == NULL)
		{
			ms->line = ft_strdup("$");
			ms->line = ft_strjoin(ms->line, var);
		}
		else
		{
			ms->line = ft_strjoin(ms->line, "$");
			ms->line = ft_strjoin(ms->line, var);
		}
	}
	else
	{
		if (ms->line == NULL)
			ms->line = ft_strdup(tmp);
		else
			ms->line = ft_strjoin(ms->line, tmp);
	}
	*j = *i;
	ft_free_string(&var);
	ft_free_string(&tmp);
}

static void	replicate_text(t_vars *ms, int *i, int *j)
{
	char	*tmp;

	tmp = ft_substr(ms->cmd_line, *j, *i - *j);
	if (ms->line == NULL)
		ms->line = ft_strdup(tmp);
	else
		ms->line = ft_strjoin(ms->line, tmp);
	ft_free_string(&tmp);
	(*i)++;
	*j = *i;
}

/* Looks for $-signs and expands if respective variable is found in envar
list. */
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
			while (ft_isalpha(ms->cmd_line[i]) == 1 || ms->cmd_line[i] == '?')
				i++;
			add_expanded_var(ms, &i, &j);
		}
		else
			i++;
	}
	replicate_text(ms, &i, &j);
	ft_free_string(&ms->cmd_line);
	ms->cmd_line = ft_strdup(ms->line);
}
