#include "../header/minishell.h"

static char	*search_for_var(t_vars *ms, char *var)
{
	t_env	*current;

	current = ms->env;
	// if (compare_string(var, "$?") == 0)					// add $? once exit status handling is done
	// 	return (ms->exit_code);
	while (current != NULL)
	{
		if (compare_str(current->name, var) == 0)
			return (current->content);
		current = current->next;
	}
	return (NULL);
}

static void	replicate_text(char **ret, char *str, int *i, int *j)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_substr(str, *j, *i - *j);
	if (*ret == NULL)
		*ret = ft_strdup(tmp);
	else
		*ret = ft_strjoin(*ret, tmp);
	free(tmp);
}

static void	add_expanded_var(t_vars *ms, char **ret, int *i, int *j)
{
	char	*tmp;
	char	*var;

	tmp = NULL;
	var = NULL;
	var = ft_substr(ms->cmd_line, *j, *i - *j);
	tmp = ft_strdup(search_for_var(ms, var));
	if (tmp == NULL)
	{
		*ret = ft_strjoin(*ret, "$");
		*ret = ft_strjoin(*ret, var);
	}
	else
		*ret = ft_strjoin(*ret, tmp);
	*j = *i;
	free(var);
	free(tmp);
}

/* Looks for $-signs and expands if respective variable is found in envar list. */
char	*dollar_expansion(t_vars *ms)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ret = NULL;
	while (ms->cmd_line[i] != '\0')
	{
		if (ms->cmd_line[i] == '$')
		{
			replicate_text(&ret, ms->cmd_line, &i, &j);
			i++;
			j = i;
			while (ft_isalpha(ms->cmd_line[i]) == 1)				// add "|| str[i] == '?'"
				i++;
			add_expanded_var(ms, &ret, &i, &j);
		}
		else
			i++;
	}
	replicate_text(&ret, ms->cmd_line, &i, &j);
	return (ret);
}
