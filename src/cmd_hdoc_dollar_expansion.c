#include "../header/minishell.h"

/* Searches if the to be expanded var is found in env list.
Returns NULL if no otherwise the expanded variable. */
static char	*search_for_var(t_vars *ms, char *var)
{
	t_env	*current;
	char	*tmp;

	tmp = NULL;
	current = ms->env;
	if (compare_str(var, "?") == 0)
	{
		tmp = ft_itoa(ms->exit_status);
		ft_free_string(&var);
		return (tmp);
	}
	while (current != NULL)
	{
		if (compare_str(current->name, var) == 0)
			return (ft_strdup(current->content));
		current = current->next;
	}
	ft_free_string(&var);
	return (NULL);
}

/* Looks for $-signs and expands if variable is found in envar list. */
char	*hdoc_dollar_expansion(t_vars *ms, char *line)
{
	int		i;
	int		j;
	char	*cpy;
	char	*envar;

	i = 0;
	j = 0;
	envar = NULL;
	cpy = ft_strdup("");
	while (line[i] != '\0')
	{
		j = i;
		while (line[i] != '$' && line[i] != '\0')
			i++;
		if (line[i] == '\0' && cpy == NULL)
			cpy = ft_strdup(line);
		else if (cpy != NULL)
			cpy = ft_strjoin(cpy, ft_substr(line, j, i));
		if (line[i] == '$')
		{
			i++;
			j = i;
			while (line[i] != '\0' && line[i] != ' ' && line[i] != '$')
				i++;
			envar = ft_substr(line, j, i - j);
			envar = search_for_var(ms, envar);
			if (envar != NULL)
			{
				j = ft_strlen(envar);
				cpy = ft_strjoin(cpy, envar);
			}
			i = i + j;
		}
	}
	return (cpy);
}


